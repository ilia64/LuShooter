// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "CharacterDataAsset.generated.h"

UCLASS(BlueprintType)
class LUSHOOTER_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FCharacterData Data;
};
