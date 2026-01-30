// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/CommonUI/BaseActivatableWidget.h"

TOptional<FUIInputConfig> UBaseActivatableWidget::GetDesiredInputConfig() const
{
	if (GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(UBaseActivatableWidget, BP_GetDesiredInputConfig)))
	{
		return BP_GetDesiredInputConfig();
	}

	return TOptional(DefaultInputConfig);
}

UWidget* UBaseActivatableWidget::NativeGetDesiredFocusTarget() const
{
	if (UWidget* Target = Super::NativeGetDesiredFocusTarget())
	{
		return Target;
	}

	return DefaultFocusTarget.Get();
}
