// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	class UImage* SlotImage;


};
