// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"

inline FName UItemDragDropOperation::GetItem() const
{
	return Item;
}

inline void UItemDragDropOperation::SetItem(const FName Value)
{
	Item = Value;
}
