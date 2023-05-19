// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(m_Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(m_FireRateTimerHandle, this, &ATower::CheckFireCondition, m_FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (m_Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), m_Tank->GetActorLocation());

		if (Distance <= m_FireRange)
		{
			return true;
		}
	}

	return false;
}

