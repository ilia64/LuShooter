// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonUI_FunctionLibrary.generated.h"

class UBaseActivatableWidget;

UCLASS()
class LUSHOOTER_API UCommonUI_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="UI")
	static TSoftClassPtr<UBaseActivatableWidget> GetWidgetClassByTag(UPARAM(meta=(Categories="UI.Widget")) const FGameplayTag Tag);
};
