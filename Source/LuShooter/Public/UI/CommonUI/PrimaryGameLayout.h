// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "PrimaryGameLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

UCLASS(Abstract, meta=(DisableNativeTick))
class LUSHOOTER_API UPrimaryGameLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UCommonActivatableWidgetContainerBase* GetLayer(const FGameplayTag Tag) const { return LayerByTag.FindRef(Tag); }

protected:
	UFUNCTION(BlueprintCallable)
	void RegisterLayer(UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag Tag, UCommonActivatableWidgetContainerBase* Container);

private:
	UPROPERTY(Transient, meta = (Categories = "UI.Layer"))
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> LayerByTag;
};
