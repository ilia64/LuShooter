// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseActivatableWidget.generated.h"

UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class LUSHOOTER_API UBaseActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
};
