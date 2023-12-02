// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/SkillSlotWidget.h"

#include "EquipmentComponent.h"
#include "ItemDragDropOperation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAssets/EquipmentItem.h"
#include "DataAssets/Item.h"
#include "Devices/Device.h"
#include "GameFramework/Character.h"

void USkillSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
		if (const ACharacter* Character = Controller->GetCharacter())
			EquipmentComponent = Character->GetComponentByClass<UEquipmentComponent>();
	SyncItem();
	SyncKey();
}

bool USkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	if (const auto Operation = Cast<UItemDragDropOperation>(InOperation))
		if (const auto Device = Operation->GetItem())
			EquipmentComponent->SetAction(Number, Device);
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

inline int32 USkillSlotWidget::GetNumber() const
{
	return Number;
}

inline FText USkillSlotWidget::GetKey() const
{
	return Key;
}

inline TSubclassOf<ADevice> USkillSlotWidget::GetItem() const
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

void USkillSlotWidget::SetItem(const TSubclassOf<ADevice> Value)
{
	Item = Value;
	SyncItem();
}

void USkillSlotWidget::SyncItem() const
{
	if (Item)
		if (const auto CDO = Item.GetDefaultObject())
			if (const auto Stats = CDO->GetStats())
				if (const auto Icon = Stats->Icon)
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
