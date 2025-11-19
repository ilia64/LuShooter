// Copyright Epic Games, Inc. All Rights Reserved.


#include "System/LuGameInstance.h"
#include "AbilitySystemGlobals.h"

void ULuGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
