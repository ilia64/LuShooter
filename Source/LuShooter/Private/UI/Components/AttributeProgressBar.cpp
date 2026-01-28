// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/AttributeProgressBar.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UAttributeProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningPlayerPawn());
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ValueAttribute).AddUObject(this, &ThisClass::OnAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxValueAttribute).AddUObject(this, &ThisClass::OnAttributeChanged);

	UpdateView();
}

void UAttributeProgressBar::ProgressChanged_Implementation(const float Progress, const float Value, const float MaxValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Cyan, FString::Printf(TEXT("%s Progress:%d %d / %d"), *ValueAttribute.AttributeName, FMath::RoundToInt(100 * Progress), FMath::RoundToInt(Value), FMath::RoundToInt(MaxValue)));
}

void UAttributeProgressBar::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue == Data.OldValue)
	{
		return;
	}

	UpdateView();
}

void UAttributeProgressBar::UpdateView()
{
	const float Value = AbilitySystemComponent->GetNumericAttribute(ValueAttribute);
	const float MaxValue = AbilitySystemComponent->GetNumericAttribute(MaxValueAttribute);
	const float Percent = Value / MaxValue;

	ProgressChanged(Percent, Value, MaxValue);
}
