// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "PrototypeCharacter.h"
#include "ItemActor.h"




void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton )
	{
		if ( SlotType == EInventorySlot_Type::InventoryItemSlot)
			SlotButton->OnClicked.AddUniqueDynamic(this, &UInventorySlot::OnEquipItem);
		else if(SlotType == EInventorySlot_Type::EquipmentSlot)
			SlotButton->OnClicked.AddUniqueDynamic(this, &UInventorySlot::OnUnEquipItem);
	}
}

void UInventorySlot::OnEquipItem()
{
	if (GetWorld())
	{
		APrototypeCharacter* PlayerCharacter = CastChecked<APrototypeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerCharacter)
		{
			for (FPrototype_ItemInfor& Item : PlayerCharacter->CurrentItems)
			{
				if (Item.InventoryImage == SlotImage)
				{
					Item.ItemStat = EItemStat::Equipped;
					break;
				}
			}

			PlayerCharacter->RefreshInventory();
		}
	}
}

void UInventorySlot::OnUnEquipItem()
{
	if (GetWorld())
	{
		APrototypeCharacter* PlayerCharacter = CastChecked<APrototypeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerCharacter)
		{
			for (FPrototype_ItemInfor& Item : PlayerCharacter->CurrentItems)
			{
				if (Item.InventoryImage == SlotImage)
				{
					Item.ItemStat = EItemStat::Unequipped;
					break;
				}
			}

			PlayerCharacter->RefreshInventory();
		}
	}
}
