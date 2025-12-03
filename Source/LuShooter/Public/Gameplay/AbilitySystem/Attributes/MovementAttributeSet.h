// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Attributes/BaseAttributeSet.h"
#include "MovementAttributeSet.generated.h"

UCLASS()
class LUSHOOTER_API UMovementAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, MaxSpeed);
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, Stamina);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_MaxSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxSpeed, Meta=(AllowPrivateAccess=true), Category="Attribute")
	FGameplayAttributeData MaxSpeed;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Meta=(AllowPrivateAccess=true), Category="Attribute")
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Meta=(AllowPrivateAccess=true), Category="Attribute")
	FGameplayAttributeData Stamina;
};
