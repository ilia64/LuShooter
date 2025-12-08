// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CheatManager.h"
#include "Lu_CheatManager.generated.h"

class UGameplayEffect;

UCLASS(Abstract)
class LUSHOOTER_API ULu_CheatManager : public UCheatManager, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void Damage(const float Amount);

	UFUNCTION(Exec, BlueprintAuthorityOnly)
	virtual void Heal(const float Amount);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageGE;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DamageSetByCallerTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> HealGE;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HealSetByCallerTag;

private:
	void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag SetByCallerTag, const float Value) const;
};
