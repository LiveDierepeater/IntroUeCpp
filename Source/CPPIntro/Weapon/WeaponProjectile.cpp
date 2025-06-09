// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"


void UWeaponProjectile::Fire() {
	Super::Fire();
	
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = GetOwner();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;    
	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, GetPlayerViewPoint(), GetPlayerViewRotation(), SpawnParam);
	if (!NewProjectile) return;
	NewProjectile->Damage = Damage;
	NewProjectile->Radius = Radius;
	NewProjectile->ImpulseStrength = ImpulseStrength;
}

FVector UWeaponProjectile::GetPlayerViewPoint() const
{
	FVector playerLocation;
	FRotator playerRotation;
	GetOwner()->GetActorEyesViewPoint(OUT playerLocation, OUT playerRotation);
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	return playerLocation;
}

FRotator UWeaponProjectile::GetPlayerViewRotation() const
{
	FVector playerLocation;
	FRotator playerRotation;
	GetOwner()->GetActorEyesViewPoint(OUT playerLocation, OUT playerRotation);
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	return playerRotation;
}
