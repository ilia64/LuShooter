// Copyright Epic Games, Inc. All Rights Reserve

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**  
 *  Приоритет:
 *   Tooltip  — 1000  (самый верхний: tooltip, hint on hover)
 *   Modal    — 600   (попапы, пауза, подтверждения)
 *   Menu     — 300   (лобби, инвентарь, карта — non-gameplay UI)
 *   Game     — 100   (HUD: прицел, здоровье, мана, хоткеи абилок)
 */

namespace UITag
{
	//Layers
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Modal);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Layer_Tooltip);

	//Widgets
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_PressAnyKey);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_GameMenu);
}
