// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "WeaponBase.h"
#include "WeaponProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CPPINTRO_API UWeaponProjectile : public UWeaponBase
{
	GENERATED_BODY()

public:    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AProjectile> Projectile;

	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Radius = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ImpulseStrength = 1000.f;
    
private:
	FVector GetPlayerViewPoint() const;
	FRotator GetPlayerViewRotation() const;
};
