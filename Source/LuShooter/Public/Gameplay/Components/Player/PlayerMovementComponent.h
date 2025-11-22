// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"


/* PlayerMovementComponent
 *  
 *  Console:
 *	p.VisualizeMovement 1
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUSHOOTER_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();
	
	virtual void BeginPlay() override;

private:
	void OnAttributeMaxSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData);
};
