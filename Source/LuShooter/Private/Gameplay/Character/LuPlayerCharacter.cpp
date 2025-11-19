// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Character/LuPlayerCharacter.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"

ALuPlayerCharacter::ALuPlayerCharacter()
{
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
