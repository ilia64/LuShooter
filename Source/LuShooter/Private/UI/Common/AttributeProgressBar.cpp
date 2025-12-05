// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Common/AttributeProgressBar.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/Image.h"

void UAttributeProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	ProgressBar_Image->SetRenderTransformPivot({0.f, 0.f});
	ProgressBar_Image->SetRenderScale({0.5, 1.f});
}

void UAttributeProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningPlayerPawn());
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ValueAttribute).AddUObject(this, &ThisClass::OnAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxValueAttribute).AddUObject(this, &ThisClass::OnAttributeChanged);

	UpdateView();
}

void UAttributeProgressBar::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue == Data.OldValue)
	{
		return;
	}

	UpdateView();
}

void UAttributeProgressBar::UpdateView() const
{
	const float Value = AbilitySystemComponent->GetNumericAttribute(ValueAttribute);
	const float MaxValue = AbilitySystemComponent->GetNumericAttribute(MaxValueAttribute);
	const float Percent = Value / MaxValue;

	ProgressBar_Image->SetRenderScale({Percent, 1.f});
}
