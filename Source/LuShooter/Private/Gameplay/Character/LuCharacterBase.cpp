// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuShooter/Public/Gameplay/Character/LuCharacterBase.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Attributes/HealthAttributeSet.h"

DEFINE_LOG_CATEGORY(LogCharacter);

ALuCharacterBase::ALuCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULuAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	HealthAttributeSet = ObjectInitializer.CreateDefaultSubobject<UHealthAttributeSet>(this, TEXT("HealthAttributeSet"));
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
		InitializeDefaultAbilities();
		InitializeDefaultEffects();
	}
}

void ALuCharacterBase::InitializeDefaultAbilities()
{
	check(AbilitySystemComponent);
	check(HasAuthority());

	for (TSubclassOf Ability : DefaultAbilities)
	{
		if (Ability.Get())
		{
			FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec{Ability});
			if (!Handle.IsValid())
			{
				UE_LOG(LogCharacter, Warning, TEXT("Failed to give ability %s to %s"), *GetNameSafe(Ability.Get()), *GetNameSafe(this));
			}
		}
		else
		{
			UE_LOG(LogCharacter, Warning, TEXT("%s has null Ability in DefaultAbilities"), *GetNameSafe(this));
		}
	}
}

void ALuCharacterBase::InitializeDefaultEffects()
{
	check(HasAuthority());

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	if (DefaultAttributes.Get())
	{
		const bool bResult = ApplyGameplayEffectToSelf(DefaultAttributes, EffectContext);
		if (bResult == false)
		{
			UE_LOG(LogCharacter, Error, TEXT("Failed to apply DefaultAttributes: %s to %s"), *GetNameSafe(DefaultAttributes.Get()), *GetNameSafe(this));
		}
	}

	for (TSubclassOf EffectClass : DefaultEffects)
	{
		if (EffectClass.Get())
		{
			const bool bResult = ApplyGameplayEffectToSelf(EffectClass, EffectContext);
			if (bResult == false)
			{
				UE_LOG(LogCharacter, Error, TEXT("Failed to apply %s to %s from DefaultEffects"), *GetNameSafe(EffectClass), *GetNameSafe(this));
			}
		}
		else
		{
			UE_LOG(LogCharacter, Warning, TEXT("%s has null gameplayEffect in DefaultEffects"), *GetNameSafe(this));
		}
	}
}

bool ALuCharacterBase::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const FGameplayEffectContextHandle& EffectContext) const
{
	check(HasAuthority());
	check(AbilitySystemComponent);
	check(EffectClass.Get());
	check(EffectContext.IsValid());

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		return EffectHandle.WasSuccessfullyApplied();
	}

	UE_LOG(LogCharacter, Error, TEXT("Failed to apply %s to %s. SpecHandle not valid!"), *GetNameSafe(EffectClass.Get()), *GetNameSafe(this));
	return false;
}
