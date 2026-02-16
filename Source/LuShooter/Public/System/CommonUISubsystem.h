// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "CommonUISubsystem.generated.h"

enum class EConfirmDialogType : uint8;
enum class EConfirmDialogButtonType : uint8;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonGlobalHintChanged, const FText, Text);

UCLASS()
class LUSHOOTER_API UCommonUISubsystem : public UCommonUISubsystemBase
{
	GENERATED_BODY()

public:
	static UCommonUISubsystem* Get(const UObject* ContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout);

	void PushWidgetAsync(const FGameplayTag LayerTag, const TSoftClassPtr<UBaseActivatableWidget> WidgetSoftClass, APlayerController* PlayerController, FOnPushedWidgetCallback OnPushedCallback = FOnPushedWidgetCallback());
	void PushConfirmDialog(const EConfirmDialogType DialogType, const FText& Title, const FText& Message, TFunction<void(const EConfirmDialogButtonType)> ButtonClickedCallback);

	void SuspendInput(const bool bValue, const FName Reason);

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonGlobalHintChanged OnButtonGlobalHintChanged;

private:
	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> PrimaryGameLayout;
};
