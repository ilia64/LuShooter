// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "Lu_PlayerController.generated.h"

struct FInputActionValue;
struct FGameplayTag;
class UPlayerInputDataAsset;

UCLASS(Abstract)
class LUSHOOTER_API ALu_PlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;

protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="123|Data")
	TObjectPtr<UPlayerInputDataAsset> InputData;

private:
	void OnLookInputAction(const FInputActionValue& Value);
	void OnMoveInputAction(const FInputActionValue& Value);

	void AbilityInputPressed(const FGameplayTag InputTag);
	void AbilityInputReleased(const FGameplayTag InputTag);
};
