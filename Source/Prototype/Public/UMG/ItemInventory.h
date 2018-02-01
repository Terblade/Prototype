// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInventory.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UItemInventory : public UUserWidget
{
	GENERATED_BODY()
	
	enum EItemNumber{MAXITEM = 15};

public:

	virtual void NativeConstruct() override;

	void Refresh(const TArray<struct FPrototype_ItemInfor>& Items);

	/*
	* item²ÛÎ»
	* Native C++ bind to UMG¿Ø¼þ
	*/
	UPROPERTY()
	TArray<class UInventorySlot*> InventorySlots;
};
