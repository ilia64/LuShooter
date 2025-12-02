// Copyright Epic Games, Inc. All Rights Reserved.


#include "LuShooter/Public/Gameplay/AbilitySystem/LuAbilitySystemComponent.h"


ULuAbilitySystemComponent::ULuAbilitySystemComponent()
{
	SetIsReplicated(true);
}

void ULuAbilitySystemComponent::AbilityInputPressed(const FGameplayTag InputTag)
{
	if (!ensureAlwaysMsgf(InputTag.IsValid(), TEXT("Invalid Tag")))
	{
		return;
	}

	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			continue;
		}

		if (Spec.IsActive())
		{
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
		}
		else
		{
			TryActivateAbility(Spec.Handle);
		}
	}
}

void ULuAbilitySystemComponent::AbilityInputReleased(const FGameplayTag InputTag)
{
	if (!ensureAlwaysMsgf(InputTag.IsValid(), TEXT("Invalid Tag")))
	{
		return;
	}

	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}
