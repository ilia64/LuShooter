// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonUISubsystem.generated.h"


class UPrimaryGameLayout;

UCLASS()
class LUSHOOTER_API UCommonUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UCommonUISubsystem* Get(const UObject* ContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void RegisterPrimaryGameLayout(UPrimaryGameLayout* InPrimaryGameLayout);

private:
	UPROPERTY(Transient)
	TObjectPtr<UPrimaryGameLayout> PrimaryGameLayout;
};
