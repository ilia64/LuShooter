// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "LuPhysicalMaterial.generated.h"

UCLASS()
class LUSHOOTER_API ULuPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PhysicalMaterial)
	TObjectPtr<USoundBase> FootstepSound;
};
