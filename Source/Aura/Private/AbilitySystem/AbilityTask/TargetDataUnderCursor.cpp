// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataUnderCursor.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::CreateTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* Myobj = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return Myobj;
}

void UTargetDataUnderCursor::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHanlde = GetAbilitySpecHandle();
		const FPredictionKey PredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHanlde, PredictionKey).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicatedCallback);
	    const bool bCallDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHanlde, PredictionKey);
		if (!bCallDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}

}

void UTargetDataUnderCursor::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC =Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	FGameplayAbilityTargetData_SingleTargetHit* Data =new FGameplayAbilityTargetData_SingleTargetHit(); 
    Data->HitResult = CursorHit;
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), 
		GetActivationPredictionKey(),DataHandle, 
		FGameplayTag(), 
		AbilitySystemComponent->ScopedPredictionKey);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag)
{
	AbilitySystemComponent.Get()->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
