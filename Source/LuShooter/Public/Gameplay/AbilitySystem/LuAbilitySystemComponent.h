// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LuAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUSHOOTER_API ULuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	ULuAbilitySystemComponent();
};
