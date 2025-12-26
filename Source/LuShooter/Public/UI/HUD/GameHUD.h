// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UBaseHUDLayout;
class UPrimaryGameLayout;

UCLASS(Abstract)
class LUSHOOTER_API AGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="123")
	TSubclassOf<UPrimaryGameLayout> PrimaryGameLayoutClass;

private:
	UFUNCTION()
	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);

private:
	UPROPERTY()
	TObjectPtr<UPrimaryGameLayout> GameLayout;

	UPROPERTY()
	TObjectPtr<UBaseHUDLayout> UnitLayout;
};
