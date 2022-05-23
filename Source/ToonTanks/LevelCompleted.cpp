// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCompleted.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULevelCompleted::ULevelCompleted()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULevelCompleted::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelCompleted::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULevelCompleted::LevelCompleted(int32 LevelNumber)
{
	if(LevelNumber > NextLevelName.Num())
	{
		UE_LOG(LogTemp,Warning,TEXT("WARNING! The number was bigger than the list of levels!!! Add it if you which to traverse to a new level!"))
		return;
	}
	UGameplayStatics::OpenLevel(this, NextLevelName[LevelNumber], false);
}

