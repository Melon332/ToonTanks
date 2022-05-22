// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Tank.h"
#include "Components/BoxComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Power Up Model"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Object"));

	RootComponent = BoxComponent;
	BaseMesh->SetupAttachment(BoxComponent);

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlap);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUp::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("I overlapped with %s"), *OtherActor->GetActorNameOrLabel());
	ATank* Tank = Cast<ATank>(OtherActor);
	if(Tank)
	{
		ActivatePowerUp(Tank);
		Destroy();
	}
}

void APowerUp::ActivatePowerUp(ATank* Tank)
{
	//Create the timer delegate and timer handle but leave them null for now.
	const FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	switch (PowerUpType)
	{
		//Create a timer delegate depending on the buff this object will give
	case AttackBoost:
		Tank->BoostAttack(AttackDamageBuffAmount);
		TimerDelegate = FTimerDelegate::CreateUObject(Tank,&ATank::SetDefaultAttackDamage);
		break;
	case SpeedBoost:
		Tank->BoostSpeed(SpeedBuffAmount);
		TimerDelegate = FTimerDelegate::CreateUObject(Tank,&ATank::SetDefaultSpeed);
		break;
	case AttackRateBoost:
		Tank->BoostAttackSpeed(AttackSpeedBuffAmount);
		TimerDelegate = FTimerDelegate::CreateUObject(Tank,&ATank::SetDefaultAttackSpeed);
		break;
		default:
			break;
	}
	//Start the timer
	CreateTimer(TimerHandle,TimerDelegate);
}

void APowerUp::CreateTimer(FTimerHandle TimerHandle, FTimerDelegate TimerDelegate)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,BuffLength,false);
}

