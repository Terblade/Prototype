// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "InventorySlot.generated.h"


enum class EInventorySlot_Type : uint8
{
	InventoryItemSlot = 0,
	EquipmentSlot,
};

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnEquipItem();

	UFUNCTION()
	void OnUnEquipItem();

public:
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* SlotImage;

	EInventorySlot_Type SlotType;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;
};
