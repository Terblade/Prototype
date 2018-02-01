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

	//virtual void NativeConstruct() override;

	void ToggleVisibility();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void ShowCharInforViewer();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharInforViewer")
	void HideCharInforViewer();

	void RefreshInventory(const TArray<struct FPrototype_ItemInfor>& Items);
	void RefreshCharacterStatsBox();

private:
	/*
	* װ���ֿ���λ
	* Native C++ bind to UMG�ؼ�
	*/
	UPROPERTY(meta = (BindWidget))
	class UItemInventory* InventoryGrid;

	bool bIsOpened;
};
