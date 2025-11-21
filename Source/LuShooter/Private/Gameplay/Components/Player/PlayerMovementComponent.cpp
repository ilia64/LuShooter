// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Components/Player/PlayerMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "Gameplay/AbilitySystem/Attributes/MovementAttributeSet.h"
#include "Gameplay/Character/LuPlayerCharacter.h"

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	const ALuPlayerCharacter* PlayerCharacter = GetOwner<ALuPlayerCharacter>();
	if (ensureAlways(PlayerCharacter))
	{
		const UMovementAttributeSet* MovementAttributeSet = PlayerCharacter->GetMovementAttributeSet();

		UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
		ASC->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetMaxSpeedAttribute()).AddUObject(this, &ThisClass::OnAttributeMaxSpeedChanged);

		MaxWalkSpeed = MovementAttributeSet->GetMaxSpeed();
	}
}

void UPlayerMovementComponent::OnAttributeMaxSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	MaxWalkSpeed = OnAttributeChangeData.NewValue;
}
