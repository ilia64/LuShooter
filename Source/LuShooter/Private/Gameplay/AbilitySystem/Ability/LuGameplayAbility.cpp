// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/AbilitySystem/Ability/LuGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "Gameplay/Character/LuCharacterBase.h"


void ULuGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ActorInfo->IsNetAuthority())
	{
		const ALuCharacterBase* Character = Cast<ALuCharacterBase>(ActorInfo->AvatarActor);

		FGameplayEffectContextHandle ContextHandle = Character->GetGameplayEffectContextSelf();
		ContextHandle.SetAbility(this);

		for (const auto& Effect : ActivationEffects)
		{
			const FActiveGameplayEffectHandle EffectHandle = Character->ApplyGameplayEffectToSelf(Effect, ContextHandle);
			if (!EffectHandle.WasSuccessfullyApplied())
			{
				UE_LOG(LogGameplayEffects, Error, TEXT("Failed to apply activation effect %s from ability %s to character %s"), *GetNameSafe(Effect.Get()), *GetNameSafe(this), *GetNameSafe(Character));
			}
		}

		for (const auto& Effect : OngoingEffects)
		{
			const FActiveGameplayEffectHandle EffectHandle = Character->ApplyGameplayEffectToSelf(Effect, ContextHandle);
			if (EffectHandle.WasSuccessfullyApplied())
			{
				OngoingEffectHandles.Add(EffectHandle);
			}
			else
			{
				UE_LOG(LogGameplayEffects, Error, TEXT("Failed to apply ongoing effect %s from ability %s to character %s"), *GetNameSafe(Effect.Get()), *GetNameSafe(this), *GetNameSafe(Character));
			}
		}
	}
}

void ULuGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ActorInfo->IsNetAuthority())
	{
		for (const auto& GameplayEffectHandle : OngoingEffectHandles)
		{
			if (GameplayEffectHandle.IsValid())
			{
				ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(GameplayEffectHandle);
			}
		}
		OngoingEffectHandles.Empty();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
