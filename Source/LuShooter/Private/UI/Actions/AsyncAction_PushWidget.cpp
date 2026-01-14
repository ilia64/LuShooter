// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Actions/AsyncAction_PushWidget.h"

#include "GameplayTagContainer.h"
#include "System/CommonUISubsystem.h"


UAsyncAction_PushWidget* UAsyncAction_PushWidget::PushWidget(const UObject* WorldContextObject, APlayerController* PlayerController, const TSoftClassPtr<UBaseActivatableWidget> WidgetClass, const FGameplayTag LayerTag, const bool bFocusOnNewlyPushedWidget)
{
	if (!ensureAlways(GEngine))
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (!ensureAlways(World))
	{
		return nullptr;
	}

	UAsyncAction_PushWidget* Node = NewObject<UAsyncAction_PushWidget>();
	Node->OwningWorld = World;
	Node->OwningPlayerController = PlayerController;
	Node->OwningWidgetClass = WidgetClass;
	Node->OwningLayerTag = LayerTag;
	Node->bOwningFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

	Node->RegisterWithGameInstance(World);
	return Node;
}

void UAsyncAction_PushWidget::Activate()
{
	UCommonUISubsystem* CommonUISubsystem = UCommonUISubsystem::Get(OwningWorld.Get());
	CommonUISubsystem->PushWidgetAsync(OwningLayerTag, OwningWidgetClass, OwningPlayerController.Get(), [this](const EPushActivatableWidgetStatus Status, UBaseActivatableWidget* Widget)
	{
		switch (Status)
		{
		case Init:
			OnInit.Broadcast(Widget);
			
		case Added:
			OnPushed.Broadcast(Widget);

		case Failed:
			OnFailed.Broadcast();
		}
	});
}
