// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == m_Tank)
	{
		m_Tank->HandleDestruction();
		if (m_Tank->GetTankPlayerController())
		{
			m_Tank->DisableInput(m_Tank->GetTankPlayerController());
			m_Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}