// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include"Player/AuraPlayerState.h"
#include "GameFrameWork/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

//Initial Ability Actor Info for serve
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

//Initial Ability Actor Info for client
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	if (!AuraPS)                 // 先别炸，等一会
	{
		// 日志+定时器或下一帧再试
		UE_LOG(LogTemp, Warning, TEXT("PlayerState not ready yet, retrying..."));
		GetWorldTimerManager().SetTimerForNextTick(this, &AAuraCharacter::InitAbilityActorInfo);
		return;
	}

	AbilitySystemComponent = AuraPS->GetAbilitySystemComponent();
	AttributeSet = AuraPS->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPS, this);

	/*AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();*/

}
