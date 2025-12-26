// Copyright Epic Games, Inc. All Rights Reserve


#include "System/CommonUISubsystem.h"

#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "UI/CommonUI/BaseActivatableWidget.h"
#include "UI/CommonUI/PrimaryGameLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

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
	check(InPrimaryGameLayout);
	PrimaryGameLayout = InPrimaryGameLayout;
}

void UCommonUISubsystem::PushWidgetAsync(const FGameplayTag LayerTag, const TSoftClassPtr<UBaseActivatableWidget> WidgetSoftClass)
{
	check(!WidgetSoftClass.IsValid());

	TWeakObjectPtr<UCommonUISubsystem> WeakThis(this);
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(WidgetSoftClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([WeakThis, LayerTag, WidgetSoftClass]()
	{
		if (const UCommonUISubsystem* StrongThis = WeakThis.Get())
		{
			const TSubclassOf<UBaseActivatableWidget> WidgetClass = WidgetSoftClass.Get();
			StrongThis->PushWidget(LayerTag, WidgetClass);
		}
	}));
}

void UCommonUISubsystem::PushWidget(const FGameplayTag LayerTag, const TSubclassOf<UBaseActivatableWidget> WidgetClass) const
{
	check(WidgetClass);

	UCommonActivatableWidgetContainerBase* LayerContainer = PrimaryGameLayout->GetLayer(LayerTag);
	check(LayerContainer);

	LayerContainer->AddWidget<UBaseActivatableWidget>(WidgetClass);
}
