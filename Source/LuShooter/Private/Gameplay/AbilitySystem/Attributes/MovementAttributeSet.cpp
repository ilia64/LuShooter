// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/AbilitySystem/Attributes/MovementAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UMovementAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UMovementAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxStaminaAttribute() && !FMath::IsNearlyEqual(OldValue, NewValue))
	{
		const float NewStamina = CalculateValueAfterMaxChange(GetStamina(), OldValue, NewValue);
		SetStamina(NewStamina);
	}
}

//		replication

void UMovementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMovementAttributeSet, MaxSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UMovementAttributeSet, MaxStamina, COND_OwnerOnly, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UMovementAttributeSet, Stamina, COND_OwnerOnly, REPNOTIFY_OnChanged);
}

void UMovementAttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMovementAttributeSet, MaxSpeed, OldValue);
}

void UMovementAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMovementAttributeSet, MaxStamina, OldValue);
}

void UMovementAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMovementAttributeSet, Stamina, OldValue);
}
