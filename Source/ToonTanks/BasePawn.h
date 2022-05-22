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
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="TestStuff")
	float FireRate{3.f};

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float DefaultFireRate{3.f};

	UPROPERTY(VisibleAnywhere, Category="TestStuff")
	float Damage{10};

	UPROPERTY(EditAnywhere, Category="Combat")
	float DefaultDamage;
	
	FTimerHandle FireRateHandler;

	void RotateTurret(FVector TargetToLookAt);

	virtual void Fire();

	virtual void CheckTimerCondition();

	UPROPERTY(EditDefaultsOnly,Category="Camera")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction();

	void SetDamage(float fDamage) { Damage = fDamage;}

private:
	UPROPERTY(VisibleDefaultsOnly, Category="Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, Category="Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category= "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Particles")
	UParticleSystem* DeathEffect;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* DeathSound;
	

};
