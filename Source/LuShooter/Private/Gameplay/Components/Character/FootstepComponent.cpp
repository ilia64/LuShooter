// Copyright Epic Games, Inc. All Rights Reserved.


#include "Gameplay/Components/Character/FootstepComponent.h"

#include "GameFramework/Character.h"
#include "Gameplay/Physics/LuPhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"


static TAutoConsoleVariable CVarShowFootsteps(TEXT("ShowDebugFootsteps"), 0, TEXT("Drow debug info about footsteps 0/1"), ECVF_Cheat);

UFootstepComponent::UFootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(false);
}

void UFootstepComponent::HandleFootstep(const EFoot Foot) const
{
	if (const ACharacter* Character = GetOwner<ACharacter>())
	{
		const int32 DebugShowFootsteps = CVarShowFootsteps.GetValueOnAnyThread();

		if (const USkeletalMeshComponent* Mesh = Character->GetMesh())
		{
			FHitResult HitResult;
			const FVector Location = Mesh->GetSocketLocation(Foot == EFoot::Left ? LeftFootSocketName : RightFootSocketName);
			const FVector TraceStart = Location + TraceStartOffset;
			const FVector TraceEnd = Location + TraceEndOffset;

			FCollisionQueryParams QueryParams;
			QueryParams.bReturnPhysicalMaterial = true;
			QueryParams.AddIgnoredActor(Character);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams))
			{
				if (HitResult.bBlockingHit)
				{
					if (HitResult.PhysMaterial.Get())
					{
						const ULuPhysicalMaterial* PhysicalMaterial = Cast<ULuPhysicalMaterial>(HitResult.PhysMaterial.Get());
						if (PhysicalMaterial && PhysicalMaterial->FootstepSound)
						{
							UGameplayStatics::PlaySoundAtLocation(this, PhysicalMaterial->FootstepSound, Location, 1.f);

							if (DebugShowFootsteps > 0)
							{
								DrawDebugSphere(GetWorld(), Location, 8, 8, FColor::Green, false, 4.f);
								DrawDebugString(GetWorld(), Location, PhysicalMaterial->GetName(), nullptr, FColor::White, 4.f);

								DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 4.f);
							}
						}
						else if (DebugShowFootsteps > 0)
						{
							DrawDebugSphere(GetWorld(), Location, 8, 8, FColor::Yellow, false, 4.f);
							DrawDebugString(GetWorld(), Location, GetNameSafe(HitResult.PhysMaterial.Get()), nullptr, FColor::Yellow, 4.f);
						}
					}
					else if (DebugShowFootsteps > 0)
					{
						DrawDebugSphere(GetWorld(), Location, 8, 8, FColor::Red, false, 4.f);
						DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 4.f);
					}
				}
				else if (DebugShowFootsteps > 0)
				{
					DrawDebugSphere(GetWorld(), Location, 8, 8, FColor::Red, false, 4.f);
					DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 4.f);
				}
			}
			else if (DebugShowFootsteps > 0)
			{
				DrawDebugSphere(GetWorld(), Location, 8, 8, FColor::Red, false, 4.f);
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 4.f);
			}
		}
	}
}
