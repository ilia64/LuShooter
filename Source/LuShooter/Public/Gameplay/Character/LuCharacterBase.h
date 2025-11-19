// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LuCharacterBase.generated.h"

enum class EGameplayEffectReplicationMode : uint8;
class ULuAbilitySystemComponent;

UCLASS(Abstract)
class LUSHOOTER_API ALuCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	explicit ALuCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="LU|Ability")
	TObjectPtr<ULuAbilitySystemComponent> AbilitySystemComponent;
};
