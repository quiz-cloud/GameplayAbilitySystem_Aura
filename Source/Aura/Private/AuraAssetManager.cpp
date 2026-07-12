// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include"AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::Get().InitializeNativeGameplayTags();
	
	UAbilitySystemGlobals::Get().InitGlobalData();
}
