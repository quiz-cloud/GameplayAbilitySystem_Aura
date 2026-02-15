// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include"Interaction/EnemyInterface.h"
#include"Interaction/CombatInterface.h"
#include "AuraEnemy.generated.h"

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
protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defualt")
	int32 Level=1;
};
