// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	class UStaticMeshComponent* m_ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category="Movement")
	class UProjectileMovementComponent* m_ProjectileMovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float m_Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* m_HitParticle;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* m_TrailParticleComp;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* m_LaunchSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* m_HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> m_HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
