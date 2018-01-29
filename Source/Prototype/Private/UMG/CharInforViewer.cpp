// Fill out your copyright notice in the Description page of Project Settings.

#include "CharInforViewer.h"



UCharInforViewer::UCharInforViewer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	,bIsOpened(false)
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

void UCharInforViewer::RefreshInventory()
{

}

void UCharInforViewer::RefreshCharacterStatsBox()
{

}
