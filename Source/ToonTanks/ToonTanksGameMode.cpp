// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == m_Tank)
	{
		m_Tank->HandleDestruction();
		if (m_ToonTanksPlayerController)
		{
			m_ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		m_TargetTowers--;

		if (m_TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	m_TargetTowers = GetTargetTowerCount();

	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	m_ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (m_ToonTanksPlayerController)
	{
		m_ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			m_ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			m_StartDelay,
			false
		);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
