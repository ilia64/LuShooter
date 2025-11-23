// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterAnimationData.generated.h"

class UCharacterAnimationDataAsset;

USTRUCT(BlueprintType)
struct FCharacterAnimationData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCharacterAnimationDataAsset> DefaultAnimationData;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBlendSpace> MovementBlendSpace;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequence> Idle;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequence> Jump;
};
