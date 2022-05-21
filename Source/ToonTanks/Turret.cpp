// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(Tank)
	{
		//Find the distance between the turret and the tank

		//Check if the tank is in range
		if(IsInRange(Tank->GetActorLocation()))
		{
			//If in range, turn to tank.
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(FireRateHandler,this, &ATurret::CheckTimerCondition, FireRate, true);
}

void ATurret::CheckTimerCondition()
{
	Super::CheckTimerCondition();
	
	if(Tank && Tank->IsAlive() && IsInRange(Tank->GetActorLocation()))
	{
		//If in range, turn to tank.
		Fire();
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

bool ATurret::IsInRange(FVector Target)
{
	return FVector::Dist(GetActorLocation(),Target) <= FireRange;
}
