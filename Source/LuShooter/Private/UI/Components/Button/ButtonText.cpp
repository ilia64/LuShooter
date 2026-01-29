// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Components/Button/ButtonText.h"

#include "CommonTextBlock.h"

void UButtonText::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetDisplayText(DisplayText);
}

void UButtonText::SetDisplayText(const FText InDisplayText)
{
	if (!InDisplayText.IsEmpty() && TextBlock)
	{
		DisplayText = InDisplayText;
		TextBlock->SetText(UseUpperCaseForDisplayText ? InDisplayText.ToUpper() : InDisplayText);
	}
}
