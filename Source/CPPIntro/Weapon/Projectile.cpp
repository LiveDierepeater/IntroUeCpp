// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

AProjectile::AProjectile() {
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = DefaultSceneRoot;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->InitBoxExtent(FVector(10.f, 10.f, 10.f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	BoxCollision->SetGenerateOverlapEvents(true);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	RadialForceComponent->Radius = Radius;
	RadialForceComponent->ImpulseStrength = ImpulseStrength;
	RadialForceComponent->bImpulseVelChange = true;
	
	this->AActor::SetLifeSpan(20.f);
	SetReplicates(true);
	AActor::SetReplicateMovement(true);
}

void AProjectile::BeginPlay() {
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if (GetOwner() == OtherActor) {
		UE_LOG(LogTemp, Error, TEXT("Hit myself"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Hit something else"));

	OnProjectileHit();

	// Origin: SweepResult->Location
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		GetActorLocation(),
		Radius,
		UDamageType::StaticClass(),
		*new TArray<AActor*>({this}),
		this,
		nullptr,
		false,
		ECC_Visibility
	);
	
	// RadialForceComponent->SetWorldLocation(GetActorLocation());
	RadialForceComponent->FireImpulse();
	
	this->Destroy();
}
