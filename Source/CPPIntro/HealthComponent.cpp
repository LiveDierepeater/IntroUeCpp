// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...E
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, Shield);
}

void UHealthComponent::HealthChecker()
{
	if (_regenerationSeconds > 0)
	{
		AddHealth(5);
		
		if (_regenerationSeconds == 1) OnRegenerationFinished.Broadcast();
		_regenerationSeconds--;
	}
	else
	{
		if (Health > 100)
		{
			Health--;
		}
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(OUT _healthCheckerTimer, this, &UHealthComponent::HealthChecker, 1, true, 0.f);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::ReceiveDamage(float damageAmount)
{
	OnReceiveDamage.Broadcast();

	bool hasShield = false;
	if (Shield > 0) hasShield = true;
	
	Shield -= damageAmount;
	if (Shield <= 0)
	{
		Health += Shield;
		Shield = 0;
		
		if (hasShield) OnReceiveDamage.Broadcast();
	}

	if (Health <= 0)
	{
		Health = 0;
		OnDeath.Broadcast();
		return true;
	}
	return false;
}

void UHealthComponent::AddHealth(float healthAmount)
{
	Health += healthAmount;
	Health = FMath::Clamp(Health, 0, MaxHealth);
}

void UHealthComponent::AddShield(float shieldAmount)
{
	Shield += shieldAmount;
	Shield = FMath::Clamp(Shield, 0, MaxShield);
}

void UHealthComponent::Regeneration(int durationInSec)
{
	_regenerationSeconds = durationInSec;
}
