// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonUISubsystem.generated.h"

struct FGameplayTag;
class UBaseActivatableWidget;
class UPrimaryGameLayout;

UCLASS()
class LUSHOOTER_API UCommonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UCommonUISubsystem* Get(const UObject* ContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout);

	void PushWidgetAsync(const FGameplayTag LayerTag, const TSoftClassPtr<UBaseActivatableWidget> WidgetSoftClass);
	void PushWidget(const FGameplayTag LayerTag, const TSubclassOf<UBaseActivatableWidget> WidgetClass) const;

private:
	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> PrimaryGameLayout;
};
