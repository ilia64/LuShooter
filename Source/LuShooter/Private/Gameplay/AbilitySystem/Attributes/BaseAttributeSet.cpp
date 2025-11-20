// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/AbilitySystem/Attributes/BaseAttributeSet.h"

float UBaseAttributeSet::CalculateValueAfterMaxChange(const float CurrentValue, const float OldMax, const float NewMax) const
{
	if (OldMax <= 0.0f || NewMax <= 0.0f)
	{
		return FMath::Max(0.0f, NewMax);
	}

	const float Percentage = CurrentValue / OldMax;
	return FMath::Clamp(Percentage * NewMax, 0.0f, NewMax);
}
