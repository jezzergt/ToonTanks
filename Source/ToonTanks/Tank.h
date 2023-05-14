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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	class USpringArmComponent* m_SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	class UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, Category="Movement")
	float m_Speed;

	void Move(float Value);

};
