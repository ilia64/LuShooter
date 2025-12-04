// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Core/Lu_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Gameplay/AbilitySystem/LuAbilitySystemComponent.h"
#include "Gameplay/Character/LuPlayerCharacter.h"
#include "Gameplay/Character/Data/Player/PlayerInputData.h"
#include "Gameplay/Components/Player/PlayerEnhancedInputComponent.h"
#include "UI/HUD/PlayerHUD.h"

class UEnhancedInputLocalPlayerSubsystem;

void ALu_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UPlayerEnhancedInputComponent* PlayerInputComponent = Cast<UPlayerEnhancedInputComponent>(InputComponent))
	{
		PlayerInputComponent->BindAction(InputData->LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLookInputAction);
		PlayerInputComponent->BindAction(InputData->MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveInputAction);

		PlayerInputComponent->BindAbilityAction(InputData->AbilityInputActions, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	}
	else
	{
		UE_LOG(LogEnhancedInput, Error, TEXT("%hs Wrong class of PlayerInputComponent"), __FUNCTION__)
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputData->GameplayInputMapping, 0);
	}
}

void ALu_PlayerController::OnLookInputAction(const FInputActionValue& Value)
{
	const FVector2D Vector = Value.Get<FVector2D>();
	AddYawInput(Vector.X);
	AddPitchInput(Vector.Y);
}

void ALu_PlayerController::OnMoveInputAction(const FInputActionValue& Value)
{
	if (APawn* CurrentPawn = GetPawn())
	{
		const FVector2D Vector2D = Value.Get<FVector2D>();
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		CurrentPawn->AddMovementInput(ForwardDirection, Vector2D.Y);
		CurrentPawn->AddMovementInput(RightDirection, Vector2D.X);
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
