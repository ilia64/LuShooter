// Copyright Epic Games, Inc. All Rights Reserve


#include "System/CommonUISubsystem.h"

#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "UI/CommonUI/BaseActivatableWidget.h"
#include "UI/CommonUI/PrimaryGameLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

DEFINE_LOG_CATEGORY(LogCommonUI);

UCommonUISubsystem* UCommonUISubsystem::Get(const UObject* ContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(ContextObject, EGetWorldErrorMode::Assert);
	return UGameInstance::GetSubsystem<UCommonUISubsystem>(World->GetGameInstance());
}

bool UCommonUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!FSlateApplication::IsInitialized() || IsRunningCommandlet() || IsRunningDedicatedServer())
	{
		return false;
	}

	TArray<UClass*> ChildClasses;
	GetDerivedClasses(GetClass(), ChildClasses, false);
	const bool bShouldCreate = ChildClasses.Num() == 0;

	return bShouldCreate && Super::ShouldCreateSubsystem(Outer);
}

void UCommonUISubsystem::RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout)
{
	PrimaryGameLayout = InPrimaryGameLayout;
	check(PrimaryGameLayout);
}

void UCommonUISubsystem::PushWidgetAsync(const FGameplayTag LayerTag, const TSoftClassPtr<UBaseActivatableWidget> WidgetSoftClass, APlayerController* PlayerController, FOnPushedWidgetCallback OnPushedCallback)
{
	check(PrimaryGameLayout);

	const UCommonActivatableWidgetContainerBase* Layer = PrimaryGameLayout->GetLayer(LayerTag);
	if (!LayerTag.IsValid() || WidgetSoftClass.IsNull() || !PlayerController || !Layer)
	{
		UE_LOG(LogCommonUI, Error, TEXT("CommonUISubsystem::PushWidgetAsync FAILED Tag:%s, WidgetSoftClass:%s, PC:%s Layer:%s"), *LayerTag.ToString(), *WidgetSoftClass.ToString(), *GetNameSafe(PlayerController), *GetNameSafe(Layer));
		ensureAlways(0);

		if (OnPushedCallback)
		{
			OnPushedCallback(Failed, nullptr);
		}

		return;
	}

	TWeakObjectPtr<UCommonUISubsystem> WeakThis(this);
	TWeakObjectPtr<APlayerController> WeakPC(PlayerController);

	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	StreamableManager.RequestAsyncLoad(WidgetSoftClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([WeakThis, LayerTag, WidgetSoftClass, WeakPC, Callback = MoveTemp(OnPushedCallback)]
	{
		if (const UCommonUISubsystem* StrongThis = WeakThis.Get())
		{
			const TSubclassOf<UBaseActivatableWidget> WidgetClass = WidgetSoftClass.Get();
			if (!WidgetClass)
			{
				UE_LOG(LogCommonUI, Error, TEXT("PushWidget: WidgetClass is null! Layer: %s"), *LayerTag.ToString());
				if (Callback)
				{
					Callback(Failed, nullptr);
				}

				return;
			}

			if (UCommonActivatableWidgetContainerBase* LayerContainer = StrongThis->PrimaryGameLayout->GetLayer(LayerTag))
			{
				UBaseActivatableWidget* Widget = LayerContainer->AddWidget<UBaseActivatableWidget>(WidgetClass, [WeakPC, Callback](UBaseActivatableWidget& InWidget)
				{
					if (WeakPC.IsValid())
					{
						InWidget.SetOwningPlayer(WeakPC.Get());
					}

					if (Callback)
					{
						Callback(Init, &InWidget);
					}
				});

				if (Widget)
				{
					if (Callback)
					{
						Callback(Added, Widget);
					}
				}
				else
				{
					UE_LOG(LogCommonUI, Error, TEXT("PushWidget: Widget is null! Layer: %s"), *LayerTag.ToString());
					if (Callback)
					{
						Callback(Failed, nullptr);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogCommonUI, Error, TEXT("PushWidget: Widget is null! Layer: %s"), *LayerTag.ToString());
			if (Callback)
			{
				Callback(Failed, nullptr);
			}
		}
	}));
}
