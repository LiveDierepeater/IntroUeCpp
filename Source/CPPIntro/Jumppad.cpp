// Fill out your copyright notice in the Description page of Project Settings.


#include "Jumppad.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AJumppad::OnTriggerOverlapped(UPrimitiveComponent* OnComponentOverlapPrimitiveComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, int BodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComponent->GetCollisionObjectType() == ECC_Pawn || OtherComponent->GetCollisionObjectType() == ECC_PhysicsBody) {
		FVector launchVelocity;
		UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), OUT launchVelocity, OtherActor->GetActorLocation(), TargetLocationBillboard->GetComponentLocation());
		OtherActor->FindComponentByClass<UCharacterMovementComponent>()->Launch(launchVelocity);
	}
}
