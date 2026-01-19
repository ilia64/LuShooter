// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "CommonUI_DeveloperSettings.generated.h"

class UBaseActivatableWidget;

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="UI Settings"))
class LUSHOOTER_API UCommonUI_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="UI Widget", meta=(ForceInlineRow, Categories="UI.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UBaseActivatableWidget>> WidgetClassByTag;
};
