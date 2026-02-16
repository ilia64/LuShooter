// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushConfirmDialog.generated.h"


enum class EConfirmDialogType : uint8;

UCLASS()
class LUSHOOTER_API UAsyncAction_PushConfirmDialog : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConfirmDialogButtonClickDelegate, const EConfirmDialogButtonType, ConfirmButtonType);

public:
	UFUNCTION(BlueprintCallable, DisplayName="Push ConfirmDialog", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category="123|Async")
	static UAsyncAction_PushConfirmDialog* PushConfirmDialog(const UObject* WorldContextObject, const EConfirmDialogType DialogType, const FText Title, const FText Message);

	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FConfirmDialogButtonClickDelegate OnConfirmed;

private:
	TWeakObjectPtr<UWorld> OwningWorld;
	EConfirmDialogType CashedDialogType;
	FText CashedTitle;
	FText CashedMessage;
};
