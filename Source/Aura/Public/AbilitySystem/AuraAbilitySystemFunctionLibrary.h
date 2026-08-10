// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include"UI/WidgetController/OverlayWidgetController.h"
#include"UI/WidgetController/AttributeMenuWidgetController.h"
#include"Data/CharacterClassInfo.h"
#include "AuraAbilitySystemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemFunctionLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemFunctionLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWC(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemFunctionLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttribute(const UObject* WorldContext, ECharacterClass CharacterClass,float Level, UAbilitySystemComponent* ASC);
};
