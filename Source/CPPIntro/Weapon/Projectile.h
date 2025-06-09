// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class CPPINTRO_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectile();
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Radius = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ImpulseStrength = 1000.f;

	UFUNCTION(BlueprintImplementableEvent, Category="Events")
	void OnProjectileHit();
    
    
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void BeginPlay() override;

};
