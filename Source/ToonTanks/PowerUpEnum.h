// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerUpEnum.generated.h"

UENUM(BlueprintType)
enum EPowerUps {
	AttackBoost = 0 UMETA(DisplayName="Attack Boost"),
	SpeedBoost = 1 UMETA(DisplayName="SpeedBoost"),
	AttackRateBoost = 2 UMETA(DisplayName="Boost Attack Rate")
};