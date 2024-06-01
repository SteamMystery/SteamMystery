// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/SkillSlotWidget.h"

#include "ItemDragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAssets/EquipmentItem.h"

void USkillSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (const auto Controller = GetOwningPlayer())
		PlayerState = Controller->GetPlayerState<AMainPlayerState>();


	SyncItem();
	SyncKey();
}

bool USkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry,
                                    const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	if (const auto Operation = Cast<UItemDragDropOperation>(InOperation))
		PlayerState->SetDevice(Number, Operation->GetItem());

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply USkillSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(RemoveKey))
	{
		UE_LOG(LogTemp, Warning, TEXT("Click"));
		PlayerState->SetDevice(Number, NAME_None);
	}

	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

inline int32 USkillSlotWidget::GetNumber() const
{
	return Number;
}

inline FText USkillSlotWidget::GetKey() const
{
	return Key;
}

inline FItem USkillSlotWidget::GetItem() const
{
	return Item;
}

void USkillSlotWidget::SetNumber(const int32 Value)
{
	Number = Value;
}

void USkillSlotWidget::SetKey(const FText Value)
{
	Key = Value;
	SyncKey();
}

void USkillSlotWidget::SetItem(const FItem Value)
{
	Item = Value;
	SyncItem();
}

void USkillSlotWidget::SyncItem() const
{
	if (const auto Icon = Item.Icon)
	{
		Image->SetBrushResourceObject(Icon);
		Image->SetRenderOpacity(1);
		return;
	}

	Image->SetRenderOpacity(0);
}

inline void USkillSlotWidget::SyncKey() const
{
	KeyTextBlock->SetText(Key);
}
