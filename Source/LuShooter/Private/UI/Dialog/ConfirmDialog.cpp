// Copyright Epic Games, Inc. All Rights Reserve


#include "UI/Dialog/ConfirmDialog.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "UI/Components/Button/TextButton.h"


FConfirmDialogInfo FConfirmDialogInfo::Create(const EConfirmDialogType DialogType, const FText& Title, const FText& Message)
{
	switch (DialogType)
	{
	case EConfirmDialogType::Ok:
		return CreateOkDialog(Title, Message);
	case EConfirmDialogType::OkCancel:
		return CreateOkCancelDialog(Title, Message);
	case EConfirmDialogType::YesNo:
		return CreateYesNoDialog(Title, Message);
	default:
		return {};
	}
}


FConfirmDialogInfo FConfirmDialogInfo::CreateOkDialog(const FText& Title, const FText& Message)
{
	FConfirmDialogInfo Info{Title, Message};
	Info.Buttons.Emplace(EConfirmDialogButtonType::Closed, FText::FromString(TEXT("Ok")));
	return Info;
}

FConfirmDialogInfo FConfirmDialogInfo::CreateYesNoDialog(const FText& Title, const FText& Message)
{
	FConfirmDialogInfo Info{Title, Message};
	Info.Buttons.Emplace(EConfirmDialogButtonType::Confirmed, FText::FromString(TEXT("Yes")));
	Info.Buttons.Emplace(EConfirmDialogButtonType::Canceled, FText::FromString(TEXT("No")));
	return Info;
}

FConfirmDialogInfo FConfirmDialogInfo::CreateOkCancelDialog(const FText& Title, const FText& Message)
{
	FConfirmDialogInfo Info{Title, Message};
	Info.Buttons.Emplace(EConfirmDialogButtonType::Confirmed, FText::FromString(TEXT("Ok")));
	Info.Buttons.Emplace(EConfirmDialogButtonType::Canceled, FText::FromString(TEXT("Cancel")));
	return Info;
}

UConfirmDialog::UConfirmDialog(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsModal = true;
}

void UConfirmDialog::InitConfirmDialog(FConfirmDialogInfo DialogInfo, TFunction<void(EConfirmDialogButtonType)> ClickButtonCallback)
{
	Title_TextBlock->SetText(DialogInfo.Title);
	Message_TextBlock->SetText(DialogInfo.Message);

	if (Buttons_Container->GetNumEntries() > 0)
	{
		Buttons_Container->Reset<UCommonButtonBase>(
			[](const UCommonButtonBase& Button)
			{
				Button.OnClicked().Clear();
			});
	}

	const UCommonInputSettings& InputSettings = ICommonInputModule::GetSettings();

	for (const FConfirmDialogButtonInfo& ButtonInfo : DialogInfo.Buttons)
	{
		FDataTableRowHandle InputActionRowHandle;
		switch (ButtonInfo.Type)
		{
		case EConfirmDialogButtonType::Confirmed:
			InputActionRowHandle = InputSettings.GetDefaultClickAction();
			break;

		default:
			InputActionRowHandle = InputSettings.GetDefaultBackAction();
			break;
		}

		UTextButton* Button = Buttons_Container->CreateEntry<UTextButton>();
		Button->SetText(ButtonInfo.Label);
		Button->SetTriggeredInputAction(InputActionRowHandle);
		Button->OnClicked().AddLambda(
			[this, ClickButtonCallback, ButtonType = ButtonInfo.Type]
			{
				ClickButtonCallback(ButtonType);

				DeactivateWidget();
			}
		);
	}

	if (Buttons_Container->GetNumEntries() > 0)
	{
		Buttons_Container->GetAllEntries().Last()->SetFocus();
	}
}
