// Fill out your copyright notice in the Description page of Project Settings.

#include "CharInforViewer.h"
#include "ItemInventory.h"
#include "WidgetBlueprintLibrary.h"
#include "PrototypeCharacter.h"
#include "ItemActor.h"
#include "InventorySlot.h"


UCharInforViewer::UCharInforViewer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryGrid(nullptr)
	, bIsOpened(false)
{

}

bool UCharInforViewer::Initialize()
{
	bool ret = Super::Initialize();

	if (HelmetSlot)
		HelmetSlot->SlotType = EInventorySlot_Type::EquipmentSlot;
	if (ShieldSlot)
		ShieldSlot->SlotType = EInventorySlot_Type::EquipmentSlot;
	if (WeaponSlot)
		WeaponSlot->SlotType = EInventorySlot_Type::EquipmentSlot;

	return ret;
}

void UCharInforViewer::ToggleVisibility()
{
	APlayerController* Controller = GetOwningPlayer();

	if (bIsOpened)
	{
		HideCharInforViewer();
		RemoveFromParent();
		bIsOpened = false;
		if (Controller)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
		}
		return;
	}

	bIsOpened = true;
	AddToViewport();
	ShowCharInforViewer();
	if (Controller)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(Controller, this);
	}
}

void UCharInforViewer::RefreshInventory(const TArray<FPrototype_ItemInfor>& Items)
{
	if (InventoryGrid)
	{
		InventoryGrid->Refresh(Items);
	}

	if (HelmetSlot && ShieldSlot && WeaponSlot)
	{
		for (const FPrototype_ItemInfor& Item : Items)
		{
			UTexture2D* EquipmentImage = Item.ItemStat == EItemStat::Equipped ? Item.InventoryImage : nullptr;
			switch (Item.ItemType)
			{
			case EItemType::Armor_Helmet:
				HelmetSlot->SlotImage = EquipmentImage;
				break;
			case EItemType::Armor_Shield:
				ShieldSlot->SlotImage = EquipmentImage;
				break;
			case EItemType::Weapon_1Handed:
				WeaponSlot->SlotImage = EquipmentImage;
				break;
			default:
				break;
			}
		}
	}
}

void UCharInforViewer::RefreshCharacterStatsBox()
{

}
