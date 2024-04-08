#include "TopDownTankProjectile.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownTankProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TopDownCharacter.h"
#include "TopDownGameMode.h"

ATopDownTankProjectile::ATopDownTankProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bReplicates = true;
	SetReplicateMovement(true);

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATopDownTankProjectile::OnProjectileBeginOverlap);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 10.0f;
}

void ATopDownTankProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATopDownGameMode* GameMode = GetWorld()->GetAuthGameMode<ATopDownGameMode>();
	if (GameMode) //Only executes in the server
	{
		if (OtherActor)
		{
			ATopDownCharacter* TankOwner = GetOwner<ATopDownCharacter>();
			if (TankOwner != nullptr && OtherActor != TankOwner)
			{
				ATopDownCharacter* HitTank = Cast<ATopDownCharacter>(OtherActor);
				if (HitTank)
				{
					GameMode->ProjectileHit(HitTank, TankOwner);
				}
				this->Destroy();
			}
		}
	}
}
