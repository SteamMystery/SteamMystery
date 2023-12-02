// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"

inline TSubclassOf<ADevice> UItemDragDropOperation::GetItem() const
{
	return Item;
}

inline void UItemDragDropOperation::SetItem(const TSubclassOf<ADevice> Value)
{
	Item = Value;
}
