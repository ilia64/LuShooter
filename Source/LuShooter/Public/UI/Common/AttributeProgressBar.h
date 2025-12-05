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
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, Category="123")
	FGameplayAttribute ValueAttribute;

	UPROPERTY(EditAnywhere, Category="123")
	FGameplayAttribute MaxValueAttribute;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> ProgressBar_Image;

private:
	void OnAttributeChanged(const FOnAttributeChangeData& Data);

	void UpdateView() const;

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
