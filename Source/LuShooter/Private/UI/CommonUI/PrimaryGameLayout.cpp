// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/CommonUI/PrimaryGameLayout.h"
#include "GameplayTagContainer.h"
#include "System/CommonUISubsystem.h"


void UPrimaryGameLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCommonUISubsystem::Get(this)->RegisterPrimaryGameLayout(this);
}

void UPrimaryGameLayout::RegisterLayer(const FGameplayTag Tag, UCommonActivatableWidgetContainerBase* Container)
{
	if (!IsDesignTime())
	{
		if (!LayerByTag.Contains(Tag))
		{
			LayerByTag.Add(Tag, Container);
		}
	}
}
