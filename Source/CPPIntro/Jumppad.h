// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teleporter.h"
#include "Jumppad.generated.h"

/**
 * 
 */
UCLASS()
class CPPINTRO_API AJumppad : public ATeleporter
{
	GENERATED_BODY()

	virtual void OnTriggerOverlapped(UPrimitiveComponent* OnComponentOverlapPrimitiveComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComponent, int BodyIndex, bool bFromSweep,
	                                 const FHitResult& SweepResult) override;
};
