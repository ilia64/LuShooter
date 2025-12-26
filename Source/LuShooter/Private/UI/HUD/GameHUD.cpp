// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/HUD/GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "System/CommonUISubsystem.h"
#include "UI/CommonUI/Lu_CommonUI.h"
#include "UI/HUD/HUDLayoutSettings.h"
#include "UI/CommonUI/PrimaryGameLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UKismetSystemLibrary::IsDedicatedServer(this))
	{
		return;
	}

	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		GameLayout = CreateWidget<UPrimaryGameLayout>(PlayerController, PrimaryGameLayoutClass);
		GameLayout->AddToViewport();

		PlayerController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPawnChanged);
		OnPawnChanged(nullptr, GetOwningPawn());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%hs: No player controller"), __FUNCTION__);
	}
}

void AGameHUD::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (OldPawn && OldPawn == NewPawn && OldPawn)
	{
		return;
	}

	UCommonActivatableWidgetContainerBase* Container = GameLayout->GetLayer(UITag::Layer_Game);
	if (!Container)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs: No Layer with tag: %s"), __FUNCTION__, *UITag::Layer_Game.GetTag().ToString());
		return;
	}

	if (UnitLayout)
	{
		Container->ClearWidgets();
		UnitLayout = nullptr;
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

	UCommonUISubsystem::Get(GetWorld())->PushWidgetAsync(UITag::Layer_Game, Settings->DefaultLayout);
}
