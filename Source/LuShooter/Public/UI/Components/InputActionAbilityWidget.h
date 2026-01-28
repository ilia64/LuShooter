// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Blueprint/UserWidget.h"
#include "InputActionAbilityWidget.generated.h"


class UImage;
class UAbilitySystemComponent;

UCLASS()
class LUSHOOTER_API UInputActionAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="AbilityActivated")
	void K2_AbilityActivated();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="AbilityEnded")
	void K2_AbilityEnded();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="AbilityCanceled")
	void K2_AbilityCanceled();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="AbilityFailed")
	void K2_AbilityFailed();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="CooldownStarted")
	void K2_CooldownStarted();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="CooldownUpdated")
	void K2_CooldownUpdated(const float Remaining, const float TotalDuration);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="CooldownEnded")
	void K2_CooldownEnded();

protected:
	UPROPERTY(EditAnywhere, Category="123")
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, Category="123")
	float CooldownMinimumTime{0.05f};

	UPROPERTY(EditAnywhere, Category="123")
	float CooldownUpdateTime{0.05f};

private:
	void ClearCurrentAbility();

	void OnAbilityActivated(UGameplayAbility* GameplayAbility);
	void OnAbilityFailed(const UGameplayAbility* GameplayAbility, const FGameplayTagContainer& GameplayTags);
	void OnAbilityEnded(UGameplayAbility* GameplayAbility);
	void OnAbilityCancelled();

	bool TryStartCooldown();
	void OnCooldownTimerTick();

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UGameplayAbility> CurrentAbility;

	FTimerHandle CooldownUpdateTimeHandle;
};
