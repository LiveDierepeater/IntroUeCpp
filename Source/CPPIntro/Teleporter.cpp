// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"


// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Static Mesh
	SM_Teleporter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = SM_Teleporter;

	// Capsule Overlap
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->SetupAttachment(SM_Teleporter);
	TriggerCapsule->SetCapsuleHalfHeight(80);
	TriggerCapsule->SetCapsuleRadius(44);
	TriggerCapsule->SetRelativeLocation(FVector(0, 0, 80));
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnTriggerOverlapped);

	// Billboard Target Location
	TargetLocationBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Target Location"));
	TargetLocationBillboard->SetupAttachment(SM_Teleporter);
	TargetLocationBillboard->SetRelativeLocation(FVector(500, 0, 0));
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleporter::OnTriggerOverlapped(UPrimitiveComponent* OnComponentOverlapPrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int BodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->FindComponentByClass<UPrimitiveComponent>()->GetCollisionObjectType() == ECC_PhysicsBody)
	{
		OtherActor->SetActorLocation(TargetLocationBillboard->GetComponentLocation());
	}
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

