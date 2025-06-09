// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "WeaponBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CPPINTRO_API UWeaponBase : public UActorComponent
{
	GENERATED_BODY()

	float DamageBase;
	float LastFired;
	
public:	
	// Sets default values for this component's properties
	UWeaponBase();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	float Damage;

	UPROPERTY(Replicated, BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	int Ammo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	int MaxAmmo;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category="WeaponComponent")
	bool IsFiring = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	float FireRate;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	UStaticMesh* WeaponStaticMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="WeaponComponent")
	UTexture2D* WeaponIcon;

	// For MuzzleFlash and Spawn Calculation
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Weapon Details")
	FVector SpawnOffset{0, 0, 0};
	UPROPERTY(BlueprintReadWrite, Category="Weapon Details")
	UStaticMeshComponent* WeaponMeshRef;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Weapon Details")
	UNiagaraSystem* MuzzleFlash;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Weapon Details")
	USoundCue* FireSound;

	UFUNCTION(Category="WeaponComponent")
	virtual void Fire();
	UFUNCTION(Category="WeaponComponent")
	virtual void SpawnMuzzleFlash();
	
	UFUNCTION(BlueprintCallable, Server, Unreliable, WithValidation, Category="WeaponComponent")
	void FireStart(float DamageMulti);
	UFUNCTION(BlueprintCallable, Server, Unreliable, WithValidation, Category="WeaponComponent")
	void FireEnd();
	
	UFUNCTION(BlueprintCallable, Category="WeaponComponent")
	void AddAmmo(int count);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Fire")
	FVector GetSpawnLocation();

	void ResetCooldown();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomEventDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Fire")
	FCustomEventDelegate OnFire;
	UPROPERTY(BlueprintAssignable, Category = "Fire")
	FCustomEventDelegate OnOutOfAmmo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FireRateTimerHandle;
	FTimerHandle FireCooldownTimerHandle;
		
};
