// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include"Interaction/EnemyInterface.h"
#include"Interaction/CombatInterface.h"
#include"UI/WidgetController/OverlayWidgetController.h"
#include"AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	/*EnemyInterface*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/*End EnemyInterface*/

	/*Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	/*Combat Interface*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defualt")
	int32 Level=1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defualt")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	virtual void InitializeDefaultAttributes() const override;
};
