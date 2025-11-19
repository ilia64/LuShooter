// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LuCharacterBase.h"
#include "LuEnemyCharacter.generated.h"

UCLASS(Abstract)
class LUSHOOTER_API ALuEnemyCharacter : public ALuCharacterBase
{
	GENERATED_BODY()

public:
	ALuEnemyCharacter();
};
