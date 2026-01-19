// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Actions/AsyncAction_PushWidget.h"

#include "GameplayTagContainer.h"
#include "System/CommonUISubsystem.h"


UAsyncAction_PushWidget* UAsyncAction_PushWidget::PushWidget(const UObject* WorldContextObject, APlayerController* PlayerController, const TSoftClassPtr<UBaseActivatableWidget> WidgetClass, const FGameplayTag LayerTag, const bool bFocusOnNewlyPushedWidget)
{
	if (!ensure(!WidgetClass.IsNull()))
	{
		UE_LOG(LogCommonUI, Error, TEXT("AsyncAction_PushWidget::PushWidget: SoftClass is NULL Tag:%s"), *LayerTag.ToString());
		return nullptr;
	}

	if (!ensure(GEngine))
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (!ensure(World))
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
	TWeakObjectPtr<UAsyncAction_PushWidget> WeakThis{this};
	UCommonUISubsystem* CommonUISubsystem = UCommonUISubsystem::Get(OwningWorld.Get());
	CommonUISubsystem->PushWidgetAsync(OwningLayerTag, OwningWidgetClass, OwningPlayerController.Get(), [WeakThis](const EPushActivatableWidgetStatus Status, UBaseActivatableWidget* Widget)
	{
		if (WeakThis.IsValid())
		{
			switch (Status)
			{
			case Init:
				WeakThis->OnInit.Broadcast(Widget);
				break;

			case Added:
				if (WeakThis->bOwningFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = Widget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}

				WeakThis->OnPushed.Broadcast(Widget);
				WeakThis->SetReadyToDestroy();
				break;

			case Failed:
				WeakThis->OnFailed.Broadcast();
				WeakThis->SetReadyToDestroy();
				break;
			}
		}
	});
}
