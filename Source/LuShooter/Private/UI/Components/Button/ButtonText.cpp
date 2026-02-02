// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/Button/ButtonText.h"

#include "CommonTextBlock.h"

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
		TextBlock->SetStyle(StyleClass);
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
