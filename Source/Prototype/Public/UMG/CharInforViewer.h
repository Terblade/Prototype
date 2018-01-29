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

	//virtual void NativeConstruct();

	void ToggleVisibility();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void ShowCharInforViewer();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void HideCharInforViewer();

	void RefreshInventory();
	void RefreshCharacterStatsBox();

private:
	/*
	* Inventoryœ‘ æ”√øÿº˛
	*/
	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class UItemInventory> InventoryUMGClass;

	bool bIsOpened;
};
