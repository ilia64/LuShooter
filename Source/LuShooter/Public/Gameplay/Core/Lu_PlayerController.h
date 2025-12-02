// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lu_PlayerController.generated.h"

struct FGameplayTag;
class UPlayerInputDataAsset;

UCLASS(Abstract)
class LUSHOOTER_API ALu_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="123|Data")
	TObjectPtr<UPlayerInputDataAsset> InputData;

private:
	void AbilityInputPressed(const FGameplayTag InputTag);
	void AbilityInputReleased(const FGameplayTag InputTag);
};
