// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks_MainMenuMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanks_MainMenuMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToonTanks_MainMenuMode();

	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
private:
	
};
