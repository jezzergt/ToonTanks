// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = m_ProjectileMesh;

	m_ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	m_TrailParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle Component"));
	m_TrailParticleComp->SetupAttachment(RootComponent);

	m_ProjectileMovementComp->InitialSpeed = 1500.f;
	m_ProjectileMovementComp->MaxSpeed = 1500.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (m_LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			m_LaunchSound,
			GetActorLocation()
		);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor, 
			m_Damage, 
			MyOwnerInstigator, 
			this, 
			DamageTypeClass
		);
		
		if (m_HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				m_HitParticle,
				GetActorLocation(),
				GetActorRotation()
			);
		}

		if (m_HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				m_HitSound,
				GetActorLocation()
			);
		}

		if (m_HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(m_HitCameraShakeClass);
		}
	}
	Destroy();
}

