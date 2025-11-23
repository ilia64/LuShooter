// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationData.h"
#include "Engine/DataAsset.h"
#include "CharacterAnimationDataAsset.generated.h"

UCLASS(BlueprintType)
class LUSHOOTER_API UCharacterAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FCharacterAnimationData Data;
};
