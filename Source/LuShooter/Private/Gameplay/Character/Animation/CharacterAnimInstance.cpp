// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Character/Animation/CharacterAnimInstance.h"

#include "Gameplay/Character/LuPlayerCharacter.h"
#include "Gameplay/Character/Data/Character/CharacterAnimationDataAsset.h"

UBlendSpace* UCharacterAnimInstance::GetLocomotionBlendSpace() const
{
	if (LocomotionBlendSpace)
	{
		return LocomotionBlendSpace;
	}

	if (const ALuPlayerCharacter* PlayerCharacter = Cast<ALuPlayerCharacter>(GetOwningActor()))
	{
		if (const UCharacterAnimationDataAsset* DataAsset = PlayerCharacter->GetAnimationData())
		{
			LocomotionBlendSpace = DataAsset->Data.MovementBlendSpace;
			if (LocomotionBlendSpace == nullptr && DataAsset->Data.DefaultAnimationData)
			{
				LocomotionBlendSpace = DataAsset->Data.DefaultAnimationData->Data.MovementBlendSpace;
			}

			return LocomotionBlendSpace;
		}
	}

	return nullptr;
}

UAnimSequence* UCharacterAnimInstance::GetIdle() const
{
	if (IdleAnimSequence)
	{
		return IdleAnimSequence;
	}

	if (const ALuPlayerCharacter* PlayerCharacter = Cast<ALuPlayerCharacter>(GetOwningActor()))
	{
		if (const UCharacterAnimationDataAsset* DataAsset = PlayerCharacter->GetAnimationData())
		{
			IdleAnimSequence = DataAsset->Data.Idle;
			if (IdleAnimSequence == nullptr && DataAsset->Data.DefaultAnimationData)
			{
				IdleAnimSequence = DataAsset->Data.DefaultAnimationData->Data.Idle;
			}

			return IdleAnimSequence;
		}
	}

	return nullptr;
}

UAnimSequence* UCharacterAnimInstance::GetJump() const
{
	if (JumpAnimSequence)
	{
		return JumpAnimSequence;
	}

	if (const ALuPlayerCharacter* PlayerCharacter = Cast<ALuPlayerCharacter>(GetOwningActor()))
	{
		if (const UCharacterAnimationDataAsset* DataAsset = PlayerCharacter->GetAnimationData())
		{
			JumpAnimSequence = DataAsset->Data.Jump;
			if (JumpAnimSequence == nullptr && DataAsset->Data.DefaultAnimationData)
			{
				JumpAnimSequence = DataAsset->Data.DefaultAnimationData->Data.Jump;
			}

			return JumpAnimSequence;
		}
	}

	return nullptr;
}
