// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class CPPINTRO_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATeleporter();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SM_Teleporter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* TriggerCapsule;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBillboardComponent* TargetLocationBillboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	virtual void OnTriggerOverlapped(UPrimitiveComponent* OnComponentOverlapPrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int BodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
