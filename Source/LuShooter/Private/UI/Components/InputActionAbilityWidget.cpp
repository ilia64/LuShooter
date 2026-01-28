// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/InputActionAbilityWidget.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


void UInputActionAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensureAlways(InputTag.IsValid()))
	{
		return;
	}

	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningPlayerPawn());
	if (ensureAlways(AbilitySystemComponent))
	{
		AbilitySystemComponent->AbilityActivatedCallbacks.AddUObject(this, &ThisClass::OnAbilityActivated);
		AbilitySystemComponent->AbilityFailedCallbacks.AddUObject(this, &ThisClass::OnAbilityFailed);
	}
}

void UInputActionAbilityWidget::OnAbilityActivated(UGameplayAbility* GameplayAbility)
{
	const FGameplayAbilitySpec* Spec = GameplayAbility->GetCurrentAbilitySpec();
	if (!Spec || !Spec->DynamicAbilityTags.HasTag(InputTag))
	{
		return;
	}

	ensureAlways(!CurrentAbility);
	ensureAlways(!CooldownUpdateTimeHandle.IsValid());

	CurrentAbility = GameplayAbility;
	CurrentAbility->OnGameplayAbilityEnded.AddUObject(this, &ThisClass::OnAbilityEnded);
	CurrentAbility->OnGameplayAbilityCancelled.AddUObject(this, &ThisClass::OnAbilityCancelled);

	K2_AbilityActivated();
}

void UInputActionAbilityWidget::OnAbilityEnded(UGameplayAbility* GameplayAbility)
{
	K2_AbilityEnded();

	const bool bHasCooldown = TryStartCooldown();
	if (!bHasCooldown)
	{
		ClearCurrentAbility();
	}
}

void UInputActionAbilityWidget::OnAbilityCancelled()
{
	ClearCurrentAbility();
}

bool UInputActionAbilityWidget::TryStartCooldown()
{
	float TimeRemaining;
	float CooldownDuration;
	CurrentAbility->GetCooldownTimeRemainingAndDuration(CurrentAbility->GetCurrentAbilitySpecHandle(), CurrentAbility->GetCurrentActorInfo(), TimeRemaining, CooldownDuration);

	if (TimeRemaining > CooldownMinimumTime)
	{
		K2_CooldownStarted();
		K2_CooldownUpdated(TimeRemaining, CooldownDuration);

		GetWorld()->GetTimerManager().SetTimer(CooldownUpdateTimeHandle, this, &ThisClass::OnCooldownTimerTick, CooldownUpdateTime, true);

		return true;
	}

	return false;
}

void UInputActionAbilityWidget::OnCooldownTimerTick()
{
	float TimeRemaining;
	float CooldownDuration;
	CurrentAbility->GetCooldownTimeRemainingAndDuration(CurrentAbility->GetCurrentAbilitySpecHandle(), CurrentAbility->GetCurrentActorInfo(), TimeRemaining, CooldownDuration);

	if (TimeRemaining > CooldownMinimumTime)
	{
		K2_CooldownUpdated(TimeRemaining, CooldownDuration);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(CooldownUpdateTimeHandle);

		K2_CooldownEnded();

		ClearCurrentAbility();
	}
}

void UInputActionAbilityWidget::OnAbilityFailed(const UGameplayAbility* GameplayAbility, const FGameplayTagContainer& GameplayTags)
{
	const FGameplayAbilitySpec* Spec = GameplayAbility->GetCurrentAbilitySpec();
	if (Spec || Spec->DynamicAbilityTags.HasTag(InputTag))
	{
		K2_AbilityFailed();
	}
}

void UInputActionAbilityWidget::ClearCurrentAbility()
{
	CurrentAbility->OnGameplayAbilityEnded.RemoveAll(this);
	CurrentAbility->OnGameplayAbilityCancelled.RemoveAll(this);
	CurrentAbility = nullptr;
}
