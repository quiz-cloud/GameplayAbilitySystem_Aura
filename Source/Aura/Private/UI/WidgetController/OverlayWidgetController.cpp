// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include"AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
}
