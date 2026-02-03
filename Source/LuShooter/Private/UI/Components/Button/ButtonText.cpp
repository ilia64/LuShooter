// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/Button/ButtonText.h"

#include "CommonTextBlock.h"
#include "System/CommonUISubsystem.h"

void UButtonText::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetDisplayText(DisplayText);
}

void UButtonText::NativeOnCurrentTextStyleChanged()
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

void UButtonText::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!GlobalHint.IsEmpty())
	{
		UCommonUISubsystem::Get(this)->OnButtonGlobalHintChanged.Broadcast(GlobalHint);
	}
}

void UButtonText::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	if (!GlobalHint.IsEmpty())
	{
		UCommonUISubsystem::Get(this)->OnButtonGlobalHintChanged.Broadcast(FText::GetEmpty());
	}
}

void UButtonText::SetDisplayText(const FText InDisplayText)
{
	if (!InDisplayText.IsEmpty() && TextBlock)
	{
		DisplayText = UseUpperCaseForDisplayText ? InDisplayText.ToUpper() : InDisplayText;
		TextBlock->SetText(DisplayText);
	}
}
