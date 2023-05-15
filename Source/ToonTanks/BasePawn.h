// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	void RotateTurret(FVector LookAtTarget);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category="Custom Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* m_CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category="Custom Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category="Custom Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category="Custom Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_ProjectileSpawn;
};
