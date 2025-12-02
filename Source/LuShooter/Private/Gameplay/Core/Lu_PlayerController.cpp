// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Core/Lu_PlayerController.h"

#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/Character/LuPlayerCharacter.h"
#include "Gameplay/Character/Data/Player/PlayerInputData.h"
#include "Gameplay/Components/Player/PlayerEnhancedInputComponent.h"

void ALu_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UPlayerEnhancedInputComponent* PlayerInputComponent = Cast<UPlayerEnhancedInputComponent>(InputComponent))
	{
		PlayerInputComponent->BindAbilityAction(InputData->AbilityInputActions, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	}
	else
	{
		UE_LOG(LogEnhancedInput, Error, TEXT("%hs Wrong class of PlayerInputComponent"), __FUNCTION__)
	}
}

void ALu_PlayerController::AbilityInputPressed(const FGameplayTag InputTag)
{
	if (ULuAbilitySystemComponent* AbilitySystemComponent = GetPawn<ALuPlayerCharacter>()->GetLuAbilitySystemComponent())
	{
		AbilitySystemComponent->AbilityInputPressed(InputTag);
	}
	else
	{
		UE_LOG(LogEnhancedInput, Error, TEXT("%hs No LuAbilitySystemComponent"), __FUNCTION__)
	}
}

void ALu_PlayerController::AbilityInputReleased(const FGameplayTag InputTag)
{
	if (ULuAbilitySystemComponent* AbilitySystemComponent = GetPawn<ALuPlayerCharacter>()->GetLuAbilitySystemComponent())
	{
		AbilitySystemComponent->AbilityInputReleased(InputTag);
	}
	else
	{
		UE_LOG(LogEnhancedInput, Error, TEXT("%hs No LuAbilitySystemComponent"), __FUNCTION__)
	}
}
