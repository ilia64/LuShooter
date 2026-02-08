// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/Button/TextButton.h"

#include "CommonTextBlock.h"
#include "System/CommonUISubsystem.h"

void UTextButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetText(DisplayText);
}

void UTextButton::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (TextBlock)
	{
		const TSubclassOf<UCommonTextStyle> StyleClass = GetCurrentTextStyleClass();
		if (StyleClass && StyleClass != GetStyle()->GetClass())
		{
			TextBlock->SetStyle(StyleClass);
		}
	}
}

void UTextButton::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!GlobalHint.IsEmpty())
	{
		UCommonUISubsystem::Get(this)->OnButtonGlobalHintChanged.Broadcast(GlobalHint);
	}
}

void UTextButton::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	if (!GlobalHint.IsEmpty())
	{
		UCommonUISubsystem::Get(this)->OnButtonGlobalHintChanged.Broadcast(FText::GetEmpty());
	}
}

void UTextButton::SetText(const FText InText)
{
	if (!InText.IsEmpty() && TextBlock)
	{
		DisplayText = UseUpperCaseForDisplayText ? InText.ToUpper() : InText;
		TextBlock->SetText(DisplayText);
	}
}
