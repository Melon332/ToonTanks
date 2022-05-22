// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}


void ATank::BoostAttackSpeed(float fAttackSpeedBuff)
{
	if(FireRate - fAttackSpeedBuff <= 0)
	{
		FireRate = 0.1;
		return;
	}
	FireRate -= fAttackSpeedBuff;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	//DIFFERENT WAY OF GETTING PLAYER CONTROLLER = UGameplayStatics::GetPlayerController(GetWorld(),0);
	TankController = Cast<APlayerController>(GetController());

	CurrentSpeed = DefaultSpeed;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ATank::Rotate);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ATank::Fire);
	PlayerInputComponent->BindAction(TEXT("QuickQuit"),IE_Pressed,this,&ATank::QuitGame);
}

void ATank::Fire()
{
	if(CanFire)
	{
		Super::Fire();
		SetFire(false);
		UE_LOG(LogTemp,Warning,TEXT("I have shoot"));
		FTimerHandle FireReset;

		FTimerDelegate FireTimer = FTimerDelegate::CreateUObject(this, &ATank::SetFire, true);

		GetWorld()->GetTimerManager().SetTimer(FireReset, FireTimer, FireRate,false);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	if(DeathCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
	}

	SetActorHiddenInGame(true);

	SetLifeState(false);
}


void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(TankController)
	{
		FHitResult HitResult;
		TankController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::Move(float value)
{
	FVector DeltaLocation(0);

	float DT = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	//X = value * DeltaTime * Speed;
	DeltaLocation.X = value * DT * CurrentSpeed; 

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Rotate(float value)
{
	FRotator rotation(0);

	float DT = UGameplayStatics::GetWorldDeltaSeconds(this);

	rotation.Yaw = value * RotationSpeed * DT;
	
	AddActorLocalRotation(rotation,true);
}

void ATank::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, TankController, EQuitPreference::Quit, false);
}


