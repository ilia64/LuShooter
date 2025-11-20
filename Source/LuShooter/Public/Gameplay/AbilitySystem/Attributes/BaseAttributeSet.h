// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"


UCLASS(Abstract)
class LUSHOOTER_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	FORCEINLINE float CalculateValueAfterMaxChange(float CurrentValue, float OldMax, float NewMax) const;
};
