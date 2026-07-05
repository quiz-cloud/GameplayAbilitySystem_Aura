// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpellAbility.h"

#include "Actor/AuraActorProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!HasAuthority(&ActivationInfo)) return;
	
}

void UAuraProjectileSpellAbility::SpawnProjectile()
{
	bool const bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
		//TODO：Set SpawnTransform Rotation
		
		AAuraActorProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraActorProjectile>(ProjectileActorClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		//TODO: Give a GameplayEffect Spec to Projectile.
		Projectile->FinishSpawning(SpawnTransform);
	}
}
