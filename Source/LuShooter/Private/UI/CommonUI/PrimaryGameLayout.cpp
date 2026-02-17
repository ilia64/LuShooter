// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/CommonUI/PrimaryGameLayout.h"
#include "GameplayTagContainer.h"
#include "System/CommonUISubsystem.h"
#include "UI/CommonUI/CommonUI_Tags.h"
#include "Widgets/CommonActivatableWidgetContainer.h"


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

			if (Tag == UITag::Layer_Modal && Container)
			{
				TWeakObjectPtr<UCommonActivatableWidgetContainerBase> WeakContainer(Container);
				Container->OnDisplayedWidgetChanged().AddLambda([WeakContainer](const UCommonActivatableWidget* DisplayedWidget)
				{
					if (UCommonActivatableWidgetContainerBase* StrongContainer = WeakContainer.Get())
					{
						StrongContainer->SetVisibility(DisplayedWidget ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
					}
				});
			}
		}
	}
}
