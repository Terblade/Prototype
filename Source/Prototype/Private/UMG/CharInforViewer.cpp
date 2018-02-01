// Fill out your copyright notice in the Description page of Project Settings.

#include "CharInforViewer.h"
#include "ItemInventory.h"


UCharInforViewer::UCharInforViewer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryGrid(nullptr)
	, bIsOpened(false)
{

}

void UCharInforViewer::ToggleVisibility()
{
	if (bIsOpened)
	{
		HideCharInforViewer();
		RemoveFromParent();
		bIsOpened = false;
		return;
	}

	bIsOpened = true;
	AddToViewport();
	ShowCharInforViewer();
}

void UCharInforViewer::RefreshInventory(const TArray<FPrototype_ItemInfor>& Items)
{
	if (InventoryGrid)
	{
		InventoryGrid->Refresh(Items);
	}
}

void UCharInforViewer::RefreshCharacterStatsBox()
{

}
