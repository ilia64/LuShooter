// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LuCharacterBase.generated.h"

struct FGameplayEffectContextHandle;
class UGameplayEffect;
class UGameplayAbility;
class ULuAbilitySystemComponent;
class UHealthAttributeSet;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Verbose, All);

UCLASS(Abstract)
class LUSHOOTER_API ALuCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	explicit ALuCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE UHealthAttributeSet* GetHealthAttributeSet() const { return HealthAttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	bool ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const FGameplayEffectContextHandle& EffectContext) const;

private:
	void InitializeDefaultAbilities();
	void InitializeDefaultEffects();

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Abilities")
	TObjectPtr<ULuAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Attributes")
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
};
