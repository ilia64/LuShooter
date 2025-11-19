// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuShooter/Public/Gameplay/Character/LuCharacterBase.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"

ALuCharacterBase::ALuCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULuAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
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
