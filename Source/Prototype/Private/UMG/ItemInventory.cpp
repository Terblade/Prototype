// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemInventory.h"
#include "InventorySlot.h"
#include "PrototypeCharacter.h"
#include "WidgetTree.h"
#include "ItemActor.h"

void UItemInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTree)
	{
		TArray<UWidget*> Slots;
		WidgetTree->GetAllWidgets(Slots);

		for(auto* Slot : Slots)
		{
			if (!Slot)
				continue;
			
			UInventorySlot* ItemSlot = Cast<UInventorySlot>(Slot);
			if (ItemSlot)
			{
				InventorySlots.AddUnique(ItemSlot);
			}
		}

		::Sort<UInventorySlot>(InventorySlots.GetData(), InventorySlots.Num()
			, [](const UInventorySlot& A, const UInventorySlot& B) -> bool{
			return A.GetName() < B.GetName();
		});
	}
	
}

void UItemInventory::Refresh(const TArray<FPrototype_ItemInfor>& Items)
{
	if (InventorySlots.Num() == 0)
		return;

	check(Items.Num() <= InventorySlots.Num());

	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		if (Items[Index].ItemStat == EItemStat::Unequipped)
		{
			InventorySlots[Index]->SlotImage = Items[Index].InventoryImage;
		}
		else
		{
			InventorySlots[Index]->SlotImage = nullptr;
		}
	}
}
