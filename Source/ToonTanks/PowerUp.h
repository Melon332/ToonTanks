// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpEnum.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class TOONTANKS_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TEnumAsByte<EPowerUps> PowerUpType;

	//Buff properties
	UPROPERTY(EditAnywhere, Category="Buffs")
	float BuffLength;

	UPROPERTY(EditAnywhere, Category="Buffs")
	float SpeedBuffAmount;

	UPROPERTY(EditAnywhere, Category="Buffs")
	float AttackDamageBuffAmount;

	UPROPERTY(EditAnywhere, Category="Buffs")
	float AttackSpeedBuffAmount;

	void ActivatePowerUp(class ATank* Tank);

	void CreateTimer(FTimerHandle TimerHandle, FTimerDelegate TimerDelegate);

};

