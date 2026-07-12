// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraActorProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class AURA_API AAuraActorProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraActorProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	virtual void Destroyed() override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	bool bHit = false;
};
