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

	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;

	void SetLifeState(bool bIsAlive) { bAlive = bIsAlive; }

	bool IsAlive() { return bAlive; }

protected:
	virtual void BeginPlay() override;

	virtual void Fire() override;
	
private:

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category="Movement")
	float RotationSpeed;

	APlayerController* TankController;

	bool bAlive{true};

	bool CanFire{true};

	void SetFire(bool bCanFire) { CanFire = bCanFire; }

	void Move(float value);
	void Rotate(float value);
	
};
