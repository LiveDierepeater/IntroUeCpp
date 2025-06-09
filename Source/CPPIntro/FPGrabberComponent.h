// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "FPGrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPINTRO_API UFPGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPGrabberComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere);
	float TraceLength = 250.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GrabActor() const;
	
	UFUNCTION(BlueprintCallable)
	void ReleaseActor() const;

private:
	AActor* Owner;
	AController* OwnerController;
	UPhysicsHandleComponent* PhysicsHandleComponent;
	
	FVector GetViewLocation() const;
	FVector GetTraceEndLocation() const;
	
	AActor* TryGetHitActor() const;
	
	void DebugDrawLine() const;
};
