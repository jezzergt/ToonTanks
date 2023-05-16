// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), m_Tank->GetActorLocation());

		if (Distance <= m_FireRange)
		{
			RotateTurret(m_Tank->GetActorLocation());
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
