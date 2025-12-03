// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Character/LuPlayerCharacter.h"

#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Attributes/MovementAttributeSet.h"
#include "Gameplay/Components/Player/PlayerMovementComponent.h"


FName ALuPlayerCharacter::MovementAttributeSetName(TEXT("MovementAttributeSet"));

ALuPlayerCharacter::ALuPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerMovementComponent>(CharacterMovementComponentName))
{
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	MovementAttributeSet = ObjectInitializer.CreateDefaultSubobject<UMovementAttributeSet>(this, MovementAttributeSetName);
}

void ALuPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
}
