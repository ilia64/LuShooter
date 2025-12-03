// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	virtual void Landed(const FHitResult& Hit) override;

	static FName MovementAttributeSetName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UMovementAttributeSet> MovementAttributeSet;

	UPROPERTY(EditAnywhere, Category="123|Tags")
	FGameplayTagContainer InAirTags;
};
