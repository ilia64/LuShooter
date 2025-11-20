// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LuCharacterBase.generated.h"

class ULuAbilitySystemComponent;
class UHealthAttributeSet;

UCLASS(Abstract)
class LUSHOOTER_API ALuCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	explicit ALuCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE UHealthAttributeSet* GetHealthAttributeSet() const { return HealthAttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Ability")
	TObjectPtr<ULuAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Attributes")
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
};
