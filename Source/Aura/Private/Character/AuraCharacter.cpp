// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include"Player/AuraPlayerState.h"
#include"Player/AuraPlayerController.h"
#include"UI/HUD/AuraHUD.h"
#include"AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>

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
	if (GetPlayerState<AAuraPlayerState>())
	{
		InitAbilityActorInfo();
		AddCharacterAbilities();
	}
	
}

//Initial Ability Actor Info for client
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (GetPlayerState<AAuraPlayerState>())
	{
		InitAbilityActorInfo();
	}

	
}

int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
