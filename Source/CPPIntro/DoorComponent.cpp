// Fill out your copyright notice in the Description page of Project Settings.



#include "DoorComponent.h"



// Sets default values for this component's properties
UDoorComponent::UDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetOpenYaw = GetOwner()->GetActorRotation().Yaw;
	TargetOpenYaw += 90.f;
	
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	SMDoor = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (AudioComponent != nullptr && SoundCue != nullptr) AudioComponent->SetSound(SoundCue);
	
	if (AudioComponent == nullptr || SoundCue == nullptr) UE_LOG(LogTemp, Error, TEXT("Something invalid"));

	if (SMDoor == nullptr) UE_LOG(LogTemp, Error, TEXT("SMC invalid"));
	
	if (!TriggerVolume) UE_LOG(LogTemp, Error, TEXT("TriggerVolume invalid"));
}


// Called every frame
void UDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetMassInTriggerVolume() >= TriggerWeight)
	{
		if (TriggerVolume)
		{
			Timer = 0.f;
			OpenDoor(DeltaTime);
		}
	}
	else if (TriggerVolume != nullptr)
	{
		Timer += DeltaTime;
		if (Timer > OpenDuration)
		{
			CloseDoor(DeltaTime);
		}
	}
}

float UDoorComponent::GetMassInTriggerVolume()
{
	float Mass = 0.f;
	if (TriggerVolume)
	{
		TArray<AActor*> OverlappingActors;
		TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

		for (const AActor* OverlappingActor : OverlappingActors)
		{
			Mass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return Mass;
}

void UDoorComponent::DoorTriggered()
{
	OnDoorTriggered.Broadcast(IsOpen);
}

void UDoorComponent::OpenDoor(float DeltaTime)
{
	if (SMDoor == nullptr) return;
	
	FRotator CurrentRotation = SMDoor->GetComponentRotation();
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, TargetOpenYaw, DoorSpeed * DeltaTime);
	SMDoor->SetWorldRotation(CurrentRotation);
	
	if (AudioComponent != nullptr && !AudioComponent->IsPlaying() && !IsOpen)
	{
		AudioComponent->Play();
		IsOpen = true;
		DoorTriggered();
	}
}

void UDoorComponent::CloseDoor(float DeltaTime)
{
	if (SMDoor == nullptr) return;
	
	FRotator CurrentRotation = SMDoor->GetComponentRotation();
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, 0, DoorSpeed * DeltaTime);
	SMDoor->SetWorldRotation(CurrentRotation);

	if (AudioComponent != nullptr && !AudioComponent->IsPlaying() && IsOpen)
	{
		AudioComponent->Play();
		IsOpen = false;
		DoorTriggered();
	}
}

