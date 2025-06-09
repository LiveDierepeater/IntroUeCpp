// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPINTRO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	int _regenerationSeconds;
	FTimerHandle _healthCheckerTimer;
	void HealthChecker();

protected:
	virtual void BeginPlay() override;

public:
	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps) const override;

	UPROPERTY(Replicated, BlueprintReadOnly, EditDefaultsOnly, Category = "Health")
	float Health = 100.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health")
	float MaxHealth = 200.f;
	
	UPROPERTY(Replicated, BlueprintReadOnly, EditDefaultsOnly, Category = "Shield")
	float Shield = 100.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Shield")
	float MaxShield = 200.f;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomEventDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FCustomEventDelegate OnReceiveDamage;
	UPROPERTY(BlueprintAssignable, Category = "Shield")
	FCustomEventDelegate OnShieldBreak;
	UPROPERTY(BlueprintAssignable, Category = "Death")
	FCustomEventDelegate OnDeath;
	UPROPERTY(BlueprintAssignable, Category = "Regeneration")
	FCustomEventDelegate OnRegenerationFinished;

	UFUNCTION(BlueprintCallable, Category = "Damage", meta = (ReturnDisplayName = "Is Lethal"))
	bool ReceiveDamage(float damageAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float healthAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Shield")
	void AddShield(float shieldAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Regeneration(int durationInSec);
};
