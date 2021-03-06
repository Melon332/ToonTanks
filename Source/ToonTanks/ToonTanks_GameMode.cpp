// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks_GameMode.h"

#include "LevelCompleted.h"
#include "MainGameInstance.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"


AToonTanks_GameMode::AToonTanks_GameMode()
{
	LevelComplete = CreateDefaultSubobject<ULevelCompleted>(TEXT("Level Completed"));
}

void AToonTanks_GameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
	if(!CurrentGameInstance)
	{
		CurrentGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(this));
		UE_LOG(LogTemp,Warning,TEXT("Got Game Instance"));
	}
}

void AToonTanks_GameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == MainPlayer)
	{
		if(TanksPlayerController)
		{
			MainPlayer->HandleDestruction();
			TanksPlayerController->SetPlayerEnableState(false);
			GameOver(false);
		}
	}
	else if(auto Turret = Cast<ATurret>(DeadActor))
	{
		Turret->HandleDestruction();
		TurretAmount--;
		if(TurretAmount <= 0)
		{
			GameOver(true);
			FinishLevel();
			if(TanksPlayerController)
			{
				TanksPlayerController->SetPlayerEnableState(false);
			}
		}
	}
}

int32 AToonTanks_GameMode::GetTargetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(),Turrets);
	return Turrets.Num();
}

void AToonTanks_GameMode::HandleGameStart()
{
	TurretAmount = GetTargetTurretCount();
	MainPlayer = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	TanksPlayerController->SetPlayerEnableState(false);

	StartGame();

	//Check if we are in the main menu, if we aren't then start the timer countdown.
	if(TanksPlayerController && !IsInMainMenu)
	{
		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(TanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,TimerDelegate,StartDelay,false);

		TanksPlayerController->SetInputModeGameOnly(false);
	}

}

void AToonTanks_GameMode::FinishLevel()
{
	LevelComplete->LevelCompleted(CurrentGameInstance->GetNextLevel());
	CurrentGameInstance->AdvanceNextLevel();
}
	
