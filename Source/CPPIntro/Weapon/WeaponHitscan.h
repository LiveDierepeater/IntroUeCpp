// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Engine/DamageEvents.h"
#include "WeaponHitscan.generated.h"

/**
 * 
 */
UCLASS()
class CPPINTRO_API UWeaponHitscan : public UWeaponBase
{
	GENERATED_BODY()
	
	virtual void Fire() override;

	FVector GetViewLocation() const;
	FVector GetViewRotation() const;
	FVector GetLineTraceEndLocation() const;

	UPROPERTY(EditDefaultsOnly)
	float Range;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	UMaterialInterface* IM_DecalMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	FVector DecalSize = FVector(6.f, 6.f, 6.f);
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	float LifeSpan = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	float FadeScreenSize = 0.0035f;
};
