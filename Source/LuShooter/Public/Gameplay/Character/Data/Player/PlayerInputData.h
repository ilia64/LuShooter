// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "PlayerInputData.generated.h"

class UInputMappingContext;
class UInputAction;


USTRUCT()
struct FPlayerInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameplayTag;
};


UCLASS(Blueprintable)
class UPlayerInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> GameplayInputMapping;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly)
	TArray<FPlayerInputAction> AbilityInputActions;
};
