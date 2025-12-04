// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


UCLASS()
class LUSHOOTER_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> Layout;
};
