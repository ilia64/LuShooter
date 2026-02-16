// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonUI/BaseActivatableWidget.h"
#include "ConfirmDialog.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;


UENUM(BlueprintType)
enum class EConfirmDialogType : uint8
{
	Ok,
	YesNo,
	OkCancel,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmDialogButtonType : uint8
{
	Confirmed,
	Canceled,
	Closed,
	Unknown UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FConfirmDialogButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EConfirmDialogButtonType Type{EConfirmDialogButtonType::Unknown};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Label;
};

USTRUCT()
struct FConfirmDialogInfo
{
	GENERATED_BODY()

	static FConfirmDialogInfo Create(const EConfirmDialogType DialogType, const FText& Title, const FText& Message);
	bool IsValid() const { return Buttons.Num() || !Message.IsEmpty(); }

	UPROPERTY(Transient)
	FText Title;

	UPROPERTY(Transient)
	FText Message;

	UPROPERTY(Transient)
	TArray<FConfirmDialogButtonInfo> Buttons;

private:
	static FConfirmDialogInfo CreateOkDialog(const FText& Title, const FText& Message);
	static FConfirmDialogInfo CreateYesNoDialog(const FText& Title, const FText& Message);
	static FConfirmDialogInfo CreateOkCancelDialog(const FText& Title, const FText& Message);
};


UCLASS(Abstract, BlueprintType, meta=(DisableNativeTick))
class LUSHOOTER_API UConfirmDialog : public UBaseActivatableWidget
{
	GENERATED_BODY()

public:
	void InitConfirmDialog(FConfirmDialogInfo DialogInfo, TFunction<void(const EConfirmDialogButtonType)> ClickButtonCallback);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Title_TextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Message_TextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDynamicEntryBox> Buttons_Container;
};
