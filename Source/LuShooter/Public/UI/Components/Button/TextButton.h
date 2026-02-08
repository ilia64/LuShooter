// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "TextButton.generated.h"

class UCommonTextBlock;

UCLASS(Abstract, Blueprintable, meta=(DisableNativeTick))
class LUSHOOTER_API UTextButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetText(const FText InText);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;

private:
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Button")
	FText DisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Button")
	bool UseUpperCaseForDisplayText{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Button")
	FText GlobalHint;
};
