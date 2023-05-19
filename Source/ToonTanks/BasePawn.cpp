// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "kismet/GameplayStatics.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	m_CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = m_CapsuleComp;

	m_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	m_BaseMesh->SetupAttachment(m_CapsuleComp);

	m_TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	m_TurretMesh->SetupAttachment(m_BaseMesh);

	m_ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	m_ProjectileSpawn->SetupAttachment(m_TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// target location minus start location gives us the appropriate vector
	FVector ToTarget = LookAtTarget - m_TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	m_TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			m_TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f)
		);
}

void ABasePawn::Fire()
{
	FVector Location = m_ProjectileSpawn->GetComponentLocation();
	FRotator Rotation = m_ProjectileSpawn->GetComponentRotation();

	GetWorld()->SpawnActor<AProjectile>(m_ProjectileClass, Location, Rotation);
}

