// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputModule.h"
#include "Gameplay/Character/Data/Player/PlayerInputData.h"
#include "PlayerEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUSHOOTER_API UPlayerEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityAction(const TArray<FPlayerInputAction>& InputDataArray, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UPlayerEnhancedInputComponent::BindAbilityAction(const TArray<FPlayerInputAction>& InputDataArray, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	for (const FPlayerInputAction& Data : InputDataArray)
	{
		if (!Data.GameplayTag.IsValid())
		{
			UE_LOG(LogEnhancedInput, Warning, TEXT("BindAbilityAction: Invalid GameplayTag"));

			continue;
		}

		if (!IsValid(Data.InputAction))
		{
			UE_LOG(LogEnhancedInput, Warning, TEXT("BindAbilityAction: Invalid InputAction"));

			continue;
		}

		if (PressedFunc)
		{
			BindAction(Data.InputAction, ETriggerEvent::Started, Object, PressedFunc, Data.GameplayTag);
		}

		if (ReleasedFunc)
		{
			BindAction(Data.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Data.GameplayTag);
		}
	}
}
