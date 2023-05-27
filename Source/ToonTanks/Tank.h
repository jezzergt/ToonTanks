// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	bool bAlive = true;

	APlayerController* GetTankPlayerController() const { return m_TankPlayerController; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	class USpringArmComponent* m_SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	class UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, Category="Movement")
	float m_Speed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float m_RotationSpeed;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* m_TankPlayerController;
};
