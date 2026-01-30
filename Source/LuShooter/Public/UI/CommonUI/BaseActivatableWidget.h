// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseActivatableWidget.generated.h"

UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class LUSHOOTER_API UBaseActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

protected:
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FUIInputConfig DefaultInputConfig{ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, false};

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TWeakObjectPtr<UWidget> DefaultFocusTarget{this};
};
