// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharInforViewer.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UCharInforViewer : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UCharInforViewer(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void ToggleVisibility();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void ShowCharInforViewer();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void HideCharInforViewer();

	void RefreshInventory(const TArray<struct FPrototype_ItemInfor>& Items);
	void RefreshCharacterStatsBox();

private:
	/*
	* 装备仓库栏位
	* Native C++ bind to UMG控件
	*/
	UPROPERTY(meta = (BindWidget))
	class UItemInventory* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UInventorySlot* HelmetSlot;

	UPROPERTY(meta = (BindWidget))
	class UInventorySlot* WeaponSlot;

	UPROPERTY(meta = (BindWidget))
	class UInventorySlot* ShieldSlot;

	bool bIsOpened;
};
