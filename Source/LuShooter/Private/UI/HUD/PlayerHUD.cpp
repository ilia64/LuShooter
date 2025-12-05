// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/HUD/PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/HUD/HUDLayoutSettings.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!UKismetSystemLibrary::IsDedicatedServer(this))
	{
		if (APlayerController* PlayerController = GetOwningPlayerController())
		{
			PlayerController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPawnChanged);
			OnPawnChanged(nullptr, GetOwningPawn());
		}
	}
}

void APlayerHUD::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (OldPawn && OldPawn == NewPawn && OldPawn)
	{
		return;
	}

	if (Layout)
	{
		Layout->RemoveFromParent();
		Layout = nullptr;
	}

	if (!NewPawn)
	{
		//TODO show no pawn layout

		return;
	}

	const UHUDLayoutSettings* Settings = GetDefault<UHUDLayoutSettings>();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs: No default layout"), __FUNCTION__);

		return;
	}

	if (Settings->DefaultLayout.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("%hs: Default layout class is Null"), __FUNCTION__);

		return;
	}

	if (UClass* LayoutClass = Settings->DefaultLayout.LoadSynchronous())
	{
		Layout = CreateWidget<UUserWidget>(GetWorld(), LayoutClass);
		Layout->AddToViewport(0);
	}
	else
	{
		ensureMsgf(0, TEXT("%hs: Can't create layout for default layout"), __FUNCTION__);
	}
}
