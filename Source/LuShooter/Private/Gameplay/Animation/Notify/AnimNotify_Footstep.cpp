// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Animation/Notify/AnimNotify_Footstep.h"

#include "Gameplay/Character/LuCharacterBase.h"
#include "Gameplay/Components/Character/FootstepComponent.h"


void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	check(MeshComp)

	if (const ALuCharacterBase* Character = MeshComp->GetOwner<ALuCharacterBase>())
	{
		const UFootstepComponent* FootstepComponent = Character->GetFootstepComponent();
		FootstepComponent->HandleFootstep(Foot);
	}
}
