// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponBase::UWeaponBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}

void UWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponBase, Ammo);
	DOREPLIFETIME(UWeaponBase, IsFiring);
}

void UWeaponBase::Fire()
{
	if (Ammo > 0)
	{
		if (MuzzleFlash && WeaponMeshRef)
			SpawnMuzzleFlash();
		else
			UE_LOG(LogTemp, Warning, TEXT("No NiagaraSystem Found!"));
		
		Ammo--;
		OnFire.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Waffe Leer!"));
		OnOutOfAmmo.Broadcast();
	}
}

void UWeaponBase::SpawnMuzzleFlash()
{
	UNiagaraComponent* System = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		MuzzleFlash,
		GetSpawnLocation(),
		WeaponMeshRef->GetComponentRotation());
}

void UWeaponBase::FireStart_Implementation(float DamageMultiplier)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (GetWorld()->GetTimeSeconds() - LastFired < 1 / FireRate) return;

		Damage = DamageBase * DamageMultiplier;
		//UE_LOG(LogTemp, Warning, TEXT("Fire Start"));
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &UWeaponBase::Fire, 1 / FireRate, true, 0.f);
		LastFired = GetWorld()->GetTimeSeconds();
		IsFiring = true;
	}
}

bool UWeaponBase::FireStart_Validate(float DamageMulti)
{
	return true;
}

void UWeaponBase::FireEnd_Implementation()
{
	if (GetOwner() && GetOwner()->HasAuthority()) {
		if (!FireRateTimerHandle.IsValid()) {
			UE_LOG(LogTemp, Error, TEXT("Handle is invalid"));
			return;
		}
    
		//UE_LOG(LogTemp, Warning, TEXT("Fire End"));
		GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
		IsFiring = false;
	}
}

bool UWeaponBase::FireEnd_Validate()
{
	return true;
}

void UWeaponBase::AddAmmo(int count)
{
	Ammo = FMath::Clamp(Ammo + count, 0, MaxAmmo);
}

FVector UWeaponBase::GetSpawnLocation()
{
	if (!WeaponMeshRef)
	{
		UE_LOG(LogTemp, Error, TEXT("No SMComponent found on Owner with tag 'WeaponMesh'"));
		return FVector::ZeroVector;
	}
	
	return WeaponMeshRef->GetComponentTransform().TransformPosition(SpawnOffset);
}

void UWeaponBase::ResetCooldown()
{
	GetWorld()->GetTimerManager().ClearTimer(FireCooldownTimerHandle);
}

// Called when the game starts
void UWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	DamageBase = Damage;
	WeaponMeshRef = GetOwner()->FindComponentByTag<UStaticMeshComponent>("WeaponMesh");
}


// Called every frame
void UWeaponBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
