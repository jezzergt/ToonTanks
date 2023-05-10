// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule_comp_ = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsule_comp_;

	base_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	base_mesh_->SetupAttachment(capsule_comp_);

	turrent_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turrent_mesh_->SetupAttachment(base_mesh_);

	projectile_spawn_point_ = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectile_spawn_point_->SetupAttachment(turrent_mesh_);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

