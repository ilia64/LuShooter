// Copyright Epic Games, Inc. All Rights Reserve


#include "Gameplay/Player/Lu_CheatManager.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UAbilitySystemComponent* ULu_CheatManager::GetAbilitySystemComponent() const
{
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOuterAPlayerController());
}

void ULu_CheatManager::Damage(const float Amount)
{
	ApplyGameplayEffectToSelf(DamageGE, DamageSetByCallerTag, Amount);
}

void ULu_CheatManager::Heal(const float Amount)
{
	ApplyGameplayEffectToSelf(HealGE, HealSetByCallerTag, Amount);
}

void ULu_CheatManager::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag SetByCallerTag, const float Value) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, ASC->MakeEffectContext());
	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(SetByCallerTag, Value);
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
