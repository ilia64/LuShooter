// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LuCharacterBase.generated.h"

struct FGameplayEffectSpecHandle;
struct FCharacterData;
struct FGameplayEffectContextHandle;
class UCharacterDataAsset;
class UCharacterAnimationDataAsset;
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
	FORCEINLINE UCharacterAnimationDataAsset* GetAnimationData() const { return AnimationData; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	FGameplayEffectContextHandle GetGameplayEffectContextSelf() const;
	bool ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const FGameplayEffectContextHandle& EffectContext) const;
	bool ApplyGameplayEffectToSelf(const FGameplayEffectSpecHandle& SpecHandle) const;

private:
	void InitializeDefaultsFromData(const FCharacterData& Data);
	void InitializeStartupAbilities();
	void InitializeStartupEffects();

private:
	UPROPERTY(EditAnywhere, Category="123|Defaults")
	TSubclassOf<UGameplayEffect> AttributeInitializerEffect;

	UPROPERTY(EditAnywhere, Category="123|Defaults")
	TSoftObjectPtr<UCharacterDataAsset> InitDataAsset;

	UPROPERTY(EditAnywhere, Category="123|Defaults")
	TObjectPtr<UCharacterAnimationDataAsset> AnimationData;

	UPROPERTY(EditAnywhere, Category="123|Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category="123|Defaults")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<ULuAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
};
