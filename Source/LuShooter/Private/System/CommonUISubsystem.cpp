// Copyright Epic Games, Inc. All Rights Reserve


#include "System/CommonUISubsystem.h"

UCommonUISubsystem* UCommonUISubsystem::Get(const UObject* ContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(ContextObject, EGetWorldErrorMode::Assert);
	return UGameInstance::GetSubsystem<UCommonUISubsystem>(World->GetGameInstance());
}

bool UCommonUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!FSlateApplication::IsInitialized() || IsRunningCommandlet() || IsRunningDedicatedServer())
	{
		return false;
	}

	TArray<UClass*> ChildClasses;
	GetDerivedClasses(GetClass(), ChildClasses, false);
	const bool bShouldCreate = ChildClasses.Num() == 0;

	return bShouldCreate && Super::ShouldCreateSubsystem(Outer);
}

void UCommonUISubsystem::RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout)
{
	check(InPrimaryGameLayout);
	PrimaryGameLayout = InPrimaryGameLayout;
}
