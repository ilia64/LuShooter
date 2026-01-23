// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "CommonUISubsystem.generated.h"

struct FGameplayTag;
class UBaseActivatableWidget;
class UPrimaryGameLayout;

UENUM()
enum EPushActivatableWidgetStatus
{
	Init,
	Added,
	Failed,
};

typedef TFunction<void (const EPushActivatableWidgetStatus, UBaseActivatableWidget*)> FOnPushedWidgetCallback;

DECLARE_LOG_CATEGORY_EXTERN(LogCommonUI, Log, All);

UCLASS()
class LUSHOOTER_API UCommonUISubsystem : public UCommonUISubsystemBase
{
	GENERATED_BODY()

public:
	static UCommonUISubsystem* Get(const UObject* ContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout);

	void PushWidgetAsync(const FGameplayTag LayerTag, const TSoftClassPtr<UBaseActivatableWidget> WidgetSoftClass, APlayerController* PlayerController, FOnPushedWidgetCallback OnPushedCallback = FOnPushedWidgetCallback());

	void SuspendInput(const bool bValue, const FName Reason);

private:
	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> PrimaryGameLayout;
};
