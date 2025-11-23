// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

UCLASS()
class LUSHOOTER_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UBlendSpace* GetLocomotionBlendSpace() const;

	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UAnimSequence* GetIdle() const;

	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UAnimSequence* GetJump() const;

private:
	UPROPERTY()
	mutable TObjectPtr<UBlendSpace> LocomotionBlendSpace;

	UPROPERTY()
	mutable TObjectPtr<UAnimSequence> IdleAnimSequence;

	UPROPERTY()
	mutable TObjectPtr<UAnimSequence> JumpAnimSequence;
};
