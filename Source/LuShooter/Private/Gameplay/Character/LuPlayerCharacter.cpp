// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Character/LuPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
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

void ALuPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	//TODO moved to PC for switching to UI (Inventory) input map.
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GameplayInputMapping, 0);
		}
	}
}

void ALuPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLookInputAction);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveInputAction);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("'%s' No Enhanced Input Component."), *GetNameSafe(this));
	}
}

void ALuPlayerCharacter::OnLookInputAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D Vector = Value.Get<FVector2D>();
		AddControllerYawInput(Vector.X);
		AddControllerPitchInput(Vector.Y);
	}
}

void ALuPlayerCharacter::OnMoveInputAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D Vector2D = Value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Vector2D.Y);
		AddMovementInput(RightDirection, Vector2D.X);
	}
}
