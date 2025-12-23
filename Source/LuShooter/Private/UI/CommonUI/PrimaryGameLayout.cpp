// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/CommonUI/PrimaryGameLayout.h"
#include "GameplayTagContainer.h"


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
