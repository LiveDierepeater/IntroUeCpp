// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHitscan.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


void UWeaponHitscan::Fire()
{
	Super::Fire();
	
	FHitResult HitResult;
	const FCollisionQueryParams CollisionQueryParams(FName(""), false, GetOwner());
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	
	GetWorld()->LineTraceSingleByObjectType(OUT HitResult, GetSpawnLocation(), GetLineTraceEndLocation(), ObjectQueryParams, CollisionQueryParams);
	
	if (!HitResult.GetActor()) return;
	//UE_LOG(LogTemp, Warning, TEXT("Type: %s"), *HitResult.GetActor()->GetName());

	if (HitResult.Component->GetCollisionObjectType() == ECC_Pawn)
	{
		FPointDamageEvent PointDamageEvent(Damage, HitResult, FVector(0.f, 0.f, 0.f), nullptr);
		HitResult.GetActor()->TakeDamage(Damage, PointDamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	}
	else if (HitResult.Component->GetCollisionObjectType() == ECC_WorldStatic)		// SpawnDecal
	{
		UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			IM_DecalMaterial,
		    DecalSize,
		    HitResult.ImpactPoint,
		    HitResult.ImpactNormal.Rotation(),
		    LifeSpan);
	}
}

FVector UWeaponHitscan::GetViewLocation() const
{
	FVector Location;
	FRotator Rotation;
	GetOwner()->GetActorEyesViewPoint(OUT Location, OUT Rotation);
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);
	return Location;
}

FVector UWeaponHitscan::GetViewRotation() const
{
	FVector Location;
	FRotator Rotation;
	GetOwner()->GetActorEyesViewPoint(OUT Location, OUT Rotation);
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);
	return Rotation.Vector();
}

FVector UWeaponHitscan::GetLineTraceEndLocation() const
{
	return GetViewLocation() + GetViewRotation() * Range;
}
