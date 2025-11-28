// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuShooter/Public/Gameplay/Character/LuCharacterBase.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Ability/LuGameplayAbility.h"
#include "Gameplay/AbilitySystem/Attributes/HealthAttributeSet.h"
#include "Gameplay/Character/Data/Character/CharacterData.h"
#include "Gameplay/Character/Data/Character/CharacterDataAsset.h"
#include "Gameplay/Components/Character/FootstepComponent.h"

DEFINE_LOG_CATEGORY(LogCharacter);

ALuCharacterBase::ALuCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULuAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	HealthAttributeSet = ObjectInitializer.CreateDefaultSubobject<UHealthAttributeSet>(this, TEXT("HealthAttributeSet"));
	FootstepComponent = ObjectInitializer.CreateDefaultSubobject<UFootstepComponent>(this, TEXT("FootstepComponent"));
}

UAbilitySystemComponent* ALuCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALuCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ALuCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		//TODO use StreamableManager under LoadSynchronous
		if (const UCharacterDataAsset* DataAsset = InitDataAsset.LoadSynchronous())
		{
			InitializeDefaultsFromData(DataAsset->Data);
		}

		InitializeStartupAbilities();
		InitializeStartupEffects();
	}
}

void ALuCharacterBase::InitializeDefaultsFromData(const FCharacterData& Data)
{
	if (AttributeInitializerEffect.Get())
	{
		const FGameplayEffectContextHandle EffectContext = GetGameplayEffectContextSelf();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AttributeInitializerEffect, 1, EffectContext);
		if (FGameplayEffectSpec* Spec = SpecHandle.Data.Get())
		{
			for (const auto& Pair : Data.AttributesByTag)
			{
				if (Pair.Key.IsValid())
				{
					Spec->SetSetByCallerMagnitude(Pair.Key, Pair.Value);
				}
				else
				{
					UE_LOG(LogCharacter, Warning, TEXT("Invalid or empty GameplayTag in AttributesByTag for character %s (effect: %s)"), *GetNameSafe(this), *GetNameSafe(AttributeInitializerEffect.Get()));
				}
			}

			const FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectToSelf(SpecHandle);
			if (!EffectHandle.WasSuccessfullyApplied())
			{
				UE_LOG(LogCharacter, Error, TEXT("Failed to apply AttributeInitializerEffect: %s to %s"), *GetNameSafe(AttributeInitializerEffect.Get()), *GetNameSafe(this));
			}
		}
		else
		{
			UE_LOG(LogCharacter, Warning, TEXT("Failed to create GameplayEffectSpec from AttributeInitializerEffect %s for character %s. Check if effect is valid and ASC is ready."), *GetNameSafe(AttributeInitializerEffect.Get()), *GetNameSafe(this));
		}
	}

	if (!Data.StartupAbilities.IsEmpty())
	{
		if (Data.OverrideNotAddStartupAbilities)
		{
			StartupAbilities.Empty();
		}

		StartupAbilities.Append(Data.StartupAbilities);
	}

	if (!Data.StartupEffects.IsEmpty())
	{
		if (Data.OverrideNotAddStartupEffects)
		{
			StartupEffects.Empty();
		}

		StartupEffects.Append(Data.StartupEffects);
	}
}

void ALuCharacterBase::InitializeStartupAbilities()
{
	check(AbilitySystemComponent);
	check(HasAuthority());

	for (TSubclassOf Ability : StartupAbilities)
	{
		if (Ability.Get())
		{
			FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec{Ability, 1, Ability.GetDefaultObject()->GetInputId()});
			if (!Handle.IsValid())
			{
				UE_LOG(LogCharacter, Warning, TEXT("Failed to give ability %s to %s"), *GetNameSafe(Ability.Get()), *GetNameSafe(this));
			}
		}
		else
		{
			UE_LOG(LogCharacter, Warning, TEXT("%s has null Ability in StartupAbilities"), *GetNameSafe(this));
		}
	}
}

void ALuCharacterBase::InitializeStartupEffects()
{
	check(HasAuthority());

	const FGameplayEffectContextHandle EffectContext = GetGameplayEffectContextSelf();
	for (TSubclassOf EffectClass : StartupEffects)
	{
		if (EffectClass.Get())
		{
			const FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectToSelf(EffectClass, EffectContext);
			if (!EffectHandle.WasSuccessfullyApplied())
			{
				UE_LOG(LogCharacter, Error, TEXT("Failed to apply %s to %s from StartupEffects"), *GetNameSafe(EffectClass), *GetNameSafe(this));
			}
		}
		else
		{
			UE_LOG(LogCharacter, Warning, TEXT("%s has null gameplayEffect in StartupEffects"), *GetNameSafe(this));
		}
	}
}

FGameplayEffectContextHandle ALuCharacterBase::GetGameplayEffectContextSelf() const
{
	check(AbilitySystemComponent);

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	return EffectContext;
}

FActiveGameplayEffectHandle ALuCharacterBase::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const FGameplayEffectContextHandle& EffectContext) const
{
	check(EffectClass.Get());
	check(EffectContext.IsValid());

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);
	return ApplyGameplayEffectToSelf(SpecHandle);
}

FActiveGameplayEffectHandle ALuCharacterBase::ApplyGameplayEffectToSelf(const FGameplayEffectSpecHandle& SpecHandle) const
{
	check(HasAuthority());
	check(AbilitySystemComponent);

	if (SpecHandle.IsValid())
	{
		return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}

	UE_LOG(LogCharacter, Error, TEXT("Attempted to apply invalid GameplayEffectSpec to character %s. SpecHandle is not valid — check effect class and AbilitySystemComponent state."), *GetNameSafe(this));
	return {};
}
