// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "TopDownTankProjectile.h"

ATopDownCharacter::ATopDownCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bReplicates = true;
	SetReplicateMovement(true);

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(RootComponent);
	TopDownCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 2500.f));
	TopDownCameraComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	TopDownCameraComponent->SetUsingAbsoluteRotation(true);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(RootComponent);
	MuzzleLocation->SetRelativeLocation(FVector::ZeroVector);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void ATopDownCharacter::FireTank()
{
	Server_FireTank();
}

void ATopDownCharacter::FireTank_Internal()
{
	if (!ensureMsgf(TankProjectileClass, TEXT("Tried to fire projectile gun, but TankProjectileClass is null")))
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (!ensureMsgf(World, TEXT("Tried to fire projectile gun, but World was null")))
	{
		return;
	}

	const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
	const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

	FActorSpawnParameters ProjectileSpawnParams;
	ProjectileSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ProjectileSpawnParams.Instigator = this;
	ProjectileSpawnParams.Owner = this;

	World->SpawnActor<ATopDownTankProjectile>(TankProjectileClass, SpawnLocation, SpawnRotation, ProjectileSpawnParams);
}

void ATopDownCharacter::Server_FireTank_Implementation()
{
	FireTank_Internal();
}

bool ATopDownCharacter::Server_FireTank_Validate()
{
	return true; // Implement server validation here if needed
}
