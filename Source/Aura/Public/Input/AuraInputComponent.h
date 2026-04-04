// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include"AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */  
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class Username,typename PressedFuncType,typename RelessedFuncType,typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, Username* Object,PressedFuncType PressedFunc, RelessedFuncType RelessedFunc,HeldFuncType HeldFunc);
};

template<class Username, typename PressedFuncType, typename RelessedFuncType, typename HeldFuncType>
inline void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, Username* Object, PressedFuncType PressedFunc, RelessedFuncType RelessedFunc, HeldFuncType HeldFunc)
{
	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (RelessedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, RelessedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc,Action.InputTag);
			}

		}
	}
}
