// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/CommonUI/CommonUI_FunctionLibrary.h"

#include "System/CommonUISubsystem.h"
#include "UI/CommonUI/CommonUI_DeveloperSettings.h"


TSoftClassPtr<UBaseActivatableWidget> UCommonUI_FunctionLibrary::GetWidgetClassByTag(const FGameplayTag Tag)
{
	if (!ensureAlways(Tag.IsValid()))
	{
		UE_LOG(LogCommonUI, Error, TEXT("CommonUI_FunctionLibrary::GetWidgetClassByTagNo: Empty Tag"));
		return nullptr;
	}

	const UCommonUI_DeveloperSettings* Settings = GetDefault<UCommonUI_DeveloperSettings>();

	TSoftClassPtr<UBaseActivatableWidget> ClassPtr = Settings->WidgetClassByTag.FindRef(Tag);
	if (ClassPtr.IsNull())
	{
		UE_LOG(LogCommonUI, Error, TEXT("No widget for tag %s"), *Tag.ToString());
		ensure(0);
	}

	return ClassPtr;
}
