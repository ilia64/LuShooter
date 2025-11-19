// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LuGameInstance.generated.h"


UCLASS()
class LUSHOOTER_API ULuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};
