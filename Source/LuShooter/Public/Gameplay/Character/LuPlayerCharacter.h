// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LuCharacterBase.h"
#include "LuPlayerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UMovementAttributeSet;

UCLASS(Abstract)
class LUSHOOTER_API ALuPlayerCharacter : public ALuCharacterBase
{
	GENERATED_BODY()

public:
	explicit ALuPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE UMovementAttributeSet* GetMovementAttributeSet() const { return MovementAttributeSet; }

	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	static FName MovementAttributeSetName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UMovementAttributeSet> MovementAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category="123|Input")
	TObjectPtr<UInputMappingContext> GameplayInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="123|Input")
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category="123|Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, Category="123|Tags")
	FGameplayTagContainer InAirTags;

private:
	void OnLookInputAction(const FInputActionValue& Value);
	void OnMoveInputAction(const FInputActionValue& Value);
};
