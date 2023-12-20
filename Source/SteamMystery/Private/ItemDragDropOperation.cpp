// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"

FName UItemDragDropOperation::GetItem() const
{
	return Item;
}

void UItemDragDropOperation::SetItem(const FName Value)
{
	Item = Value;
}
