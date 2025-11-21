// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include "HealthAttributeSet.generated.h"

/**
 *	Health, Damage and Healing
 *  Console: ~ AbilitySystem.DebugAttribute Health
 */

UCLASS()
class LUSHOOTER_API UHealthAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Healing);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Damage);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Meta=(AllowPrivateAccess=true), Category="Attribute")
	FGameplayAttributeData MaxHealth;

	// HideFromModifiers - no direct modifications use Healing or Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Meta=(HideFromModifiers, AllowPrivateAccess=true), Category="Attribute")
	FGameplayAttributeData Health;

	UPROPERTY()
	FGameplayAttributeData Healing;

	UPROPERTY()
	FGameplayAttributeData Damage;
};
