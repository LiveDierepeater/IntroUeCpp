// Fill out your copyright notice in the Description page of Project Settings.


#include "FPGrabberComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"


// Sets default values for this component's properties
UFPGrabberComponent::UFPGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFPGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	if (!Owner) UE_LOG(LogTemp, Error, TEXT("No Owner Found"));
	
	OwnerController = GetWorld()->GetFirstPlayerController();
	if (!OwnerController) UE_LOG(LogTemp, Error, TEXT("No OwnerController Found"));
	
	PhysicsHandleComponent = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent) UE_LOG(LogTemp, Error, TEXT("No PhysicsHandleComponent Found"));
}


// Called every frame
void UFPGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//DebugDrawLine();
	if (PhysicsHandleComponent)
		PhysicsHandleComponent->SetTargetLocation(GetTraceEndLocation());
	
	//if (HitActor) UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
}

void UFPGrabberComponent::GrabActor() const
{
	const AActor* ActorToGrab = TryGetHitActor();

	if (!PhysicsHandleComponent || !ActorToGrab) return;
	//UE_LOG(LogTemp, Warning, TEXT("Grab"));
	
	PhysicsHandleComponent->GrabComponentAtLocation(
		ActorToGrab->FindComponentByClass<UPrimitiveComponent>(),
		FName(""),
		ActorToGrab->GetActorLocation());
}

void UFPGrabberComponent::ReleaseActor() const
{
	//UE_LOG(LogTemp, Warning, TEXT("Release"));
	PhysicsHandleComponent->ReleaseComponent();
}

FVector UFPGrabberComponent::GetViewLocation() const
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	OwnerController->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);
	
	return PlayerViewLocation;
}

FVector UFPGrabberComponent::GetTraceEndLocation() const
{
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	OwnerController->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	const FVector LineTraceEndLocation = PlayerViewRotation.Vector() * TraceLength + PlayerViewLocation;
	return LineTraceEndLocation;
}

AActor* UFPGrabberComponent::TryGetHitActor() const
{
	FHitResult HitResult;
	const FCollisionQueryParams CollisionQueryParams(FName(""), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetViewLocation(),
		GetTraceEndLocation(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		CollisionQueryParams);
	
	return HitResult.GetActor();
}

void UFPGrabberComponent::DebugDrawLine() const
{
	DrawDebugLine(GetWorld(), GetViewLocation(), GetTraceEndLocation(), FColor::Red, false, 0.2f);
}
