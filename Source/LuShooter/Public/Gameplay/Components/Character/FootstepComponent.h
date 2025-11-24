// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepComponent.generated.h"

UENUM(BlueprintType)
enum class EFoot : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUSHOOTER_API UFootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootstepComponent();

	void HandleFootstep(const EFoot Foot) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="123|Footstep")
	FName LeftFootSocketName{TEXT("LeftFootSocket")};

	UPROPERTY(EditDefaultsOnly, Category="123|Footstep")
	FName RightFootSocketName{TEXT("RightFootSocket")};

	UPROPERTY(EditDefaultsOnly, Category="123|Footstep")
	FVector TraceStartOffset{FVector::UpVector * 20.f};

	UPROPERTY(EditDefaultsOnly, Category="123|Footstep")
	FVector TraceEndOffset{FVector::DownVector * 30.f};
};
