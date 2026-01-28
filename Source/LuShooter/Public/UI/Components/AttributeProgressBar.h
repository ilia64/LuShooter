// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "AttributeProgressBar.generated.h"

struct FOnAttributeChangeData;
class UImage;

UCLASS()
class LUSHOOTER_API UAttributeProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent)
	void ProgressChanged(const float Progress, const float Value, const float MaxValue);

protected:
	UPROPERTY(EditAnywhere, Category="123")
	FGameplayAttribute ValueAttribute;

	UPROPERTY(EditAnywhere, Category="123")
	FGameplayAttribute MaxValueAttribute;

private:
	void OnAttributeChanged(const FOnAttributeChangeData& Data);

	void UpdateView();

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
