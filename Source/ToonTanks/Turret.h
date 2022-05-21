// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

	virtual void CheckTimerCondition() override;
	
private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category="Shooting Properties")
	float FireRange;

	bool IsInRange(FVector Target);
	
};
