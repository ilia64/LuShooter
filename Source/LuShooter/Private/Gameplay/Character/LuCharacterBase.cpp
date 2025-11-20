// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuShooter/Public/Gameplay/Character/LuCharacterBase.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Attributes/HealthAttributeSet.h"

ALuCharacterBase::ALuCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULuAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	HealthAttributeSet = ObjectInitializer.CreateDefaultSubobject<UHealthAttributeSet>(this, TEXT("HealthAttributes"));
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
