// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LuCharacterBase.h"
#include "LuPlayerCharacter.generated.h"

class UMovementAttributeSet;

UCLASS(Abstract)
class LUSHOOTER_API ALuPlayerCharacter : public ALuCharacterBase
{
	GENERATED_BODY()

public:
	explicit ALuPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE UMovementAttributeSet* GetMovementAttributeSet() const { return MovementAttributeSet; }

public:
	static FName MovementAttributeSetName;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UMovementAttributeSet> MovementAttributeSet;
};
