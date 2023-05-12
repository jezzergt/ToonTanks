// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	m_SpringArm->SetupAttachment(RootComponent);

	m_CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_CameraComp->SetupAttachment(m_SpringArm);
}
