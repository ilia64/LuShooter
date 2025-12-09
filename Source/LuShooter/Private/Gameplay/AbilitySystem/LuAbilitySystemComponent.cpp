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
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			Spec.InputPressed = true;

			if (Spec.IsActive())
			{
				//For AbilityTask WaitInputPressed
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
			}
			else
			{
				TryActivateAbility(Spec.Handle);
			}
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
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.IsActive() && Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			Spec.InputPressed = false;

			// both methods -> UGameplayAbility::InputReleased(...);
			if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
			{
				ServerSetInputReleased(Spec.Handle);
			}

			AbilitySpecInputReleased(Spec);

			//For AbilityTask WaitInputRelease
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}
