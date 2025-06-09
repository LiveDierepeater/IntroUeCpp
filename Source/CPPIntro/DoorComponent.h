// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "DoorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorTriggeredDelegate, bool, IsOpen);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPINTRO_API UDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorComponent();
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float DoorSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float OpenDuration = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	USoundCue* SoundCue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	float TriggerWeight = 55.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetMassInTriggerVolume();

	// Multicast Delegate, das wie ein Event-Node in Blueprints erscheint
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FDoorTriggeredDelegate OnDoorTriggered;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void DoorTriggered();

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	
	AActor* Player;
	UAudioComponent* AudioComponent;
	UStaticMeshComponent* SMDoor;
	
	float TargetOpenYaw;
	bool IsOpen = false;

	float Timer;
		
};
