// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LuGameplayAbility.generated.h"

UCLASS(Abstract)
class LUSHOOTER_API ULuGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FORCEINLINE FGameplayTag GetInputTag() const { return InputTag; };

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TArray<TSubclassOf<UGameplayEffect>> OngoingEffects;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TArray<TSubclassOf<UGameplayEffect>> ActivationEffects;

private:
	TArray<FActiveGameplayEffectHandle> OngoingEffectHandles;
};
