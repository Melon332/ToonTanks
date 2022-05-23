// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanks_GameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	void ActorDied(AActor* DeadActor);

	AToonTanks_GameMode();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* MainPlayer;
	class AToonTanksPlayerController* TanksPlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float StartDelay{3.f};

	int32 TurretAmount{0};
	int32 GetTargetTurretCount();

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsInMainMenu;

	UPROPERTY(EditAnywhere)
	class ULevelCompleted* LevelComplete;

	UPROPERTY(VisibleAnywhere)
	int32 NextLevelNumber{0};

	class UMainGameInstance* CurrentGameInstance;

	void HandleGameStart();

	void FinishLevel();
};
