// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Actions/AsyncAction_PushConfirmDialog.h"

#include "System/CommonUISubsystem.h"
#include "UI/Dialog/ConfirmDialog.h"

UAsyncAction_PushConfirmDialog* UAsyncAction_PushConfirmDialog::PushConfirmDialog(const UObject* WorldContextObject, const EConfirmDialogType DialogType, const FText Title, const FText Message)
{
	if (!ensure(GEngine))
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (!ensure(World))
	{
		return nullptr;
	}

	UAsyncAction_PushConfirmDialog* Node = NewObject<UAsyncAction_PushConfirmDialog>();
	Node->OwningWorld = World;
	Node->CashedDialogType = DialogType;
	Node->CashedTitle = Title;
	Node->CashedMessage = Message;

	Node->RegisterWithGameInstance(World);

	return Node;
}

void UAsyncAction_PushConfirmDialog::Activate()
{
	Super::Activate();

	TWeakObjectPtr<UAsyncAction_PushConfirmDialog> WeakThis{this};
	UCommonUISubsystem::Get(OwningWorld.Get())->PushConfirmDialog(
		CashedDialogType,
		CashedTitle,
		CashedMessage,
		[WeakThis](const EConfirmDialogButtonType ConfirmButtonType)
		{
			if (WeakThis.IsValid())
			{
				WeakThis->OnConfirmed.Broadcast(ConfirmButtonType);
				WeakThis->SetReadyToDestroy();
			}
		});
}
