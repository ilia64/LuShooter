// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Character/LuEnemyCharacter.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"

ALuEnemyCharacter::ALuEnemyCharacter()
{
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}
