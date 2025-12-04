// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDLayout.h"
#include "Engine/DeveloperSettings.h"
#include "HUDLayoutSettings.generated.h"

struct FGameplayTag;

UCLASS(Config=Game, defaultconfig, meta = (DisplayName="HUD"))
class LUSHOOTER_API UHUDLayoutSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditDefaultsOnly)
	TSoftClassPtr<UBaseHUDLayout> DefaultLayout;

	/** 
	 * TODO: HUD Layout style and logic by PawnType 
	 * Tags: Unit.Hero, Unit.Enemy, Unit.Drone, Unit.Vehicle
	 * 
	 * UPROPERTY(config, EditDefaultsOnly) 
	 * TMap<FGameplayTag, TSoftClassPtr<UBaseHUDLayout>> LayoutByUnit;
	 */
};
