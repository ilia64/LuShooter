// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UI/CommonUI/BaseActivatableWidget.h"
#include "AsyncAction_PushWidget.generated.h"

class UBaseActivatableWidget;

UCLASS()
class LUSHOOTER_API UAsyncAction_PushWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPushWidgetDelegate, UBaseActivatableWidget*, Widget);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPushWidgetFailedDelegate);

public:
	UFUNCTION(BlueprintCallable, DisplayName="Push Widget", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category="123|Async")
	static UAsyncAction_PushWidget* PushWidget(const UObject* WorldContextObject,
	                                           APlayerController* PlayerController,
	                                           const TSoftClassPtr<UBaseActivatableWidget> WidgetClass,
	                                           UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag LayerTag,
	                                           const bool bFocusOnNewlyPushedWidget = true);


	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FPushWidgetDelegate OnInit;

	UPROPERTY(BlueprintAssignable)
	FPushWidgetDelegate OnPushed;

	UPROPERTY(BlueprintAssignable)
	FPushWidgetFailedDelegate OnFailed;

private:
	TWeakObjectPtr<UWorld> OwningWorld;
	TWeakObjectPtr<APlayerController> OwningPlayerController;
	TSoftClassPtr<UBaseActivatableWidget> OwningWidgetClass;
	FGameplayTag OwningLayerTag;
	bool bOwningFocusOnNewlyPushedWidget{true};
};
