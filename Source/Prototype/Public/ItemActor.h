// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"



UENUM()
enum class EItemType : uint8
{
	Weapon_1Handed = 0,
	Weapon_2Handed,
	Armor_Shield,
	Armor_Helmet,
	consumable
};

enum class EItemStat : uint8
{
	Unequipped = 0,
	Equipped,
};

UCLASS(config = Game, BlueprintType)
class PROTOTYPE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

	virtual void Tick(float DeltaSeconds);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	void OnPickupItem(class APrototypeCharacter* Player);

	/* Delegates */
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///* Delegates */
	UFUNCTION()
	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	/** Sphere component used for collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* TriggerCollision;
	/*
	* 预览模型
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PreviewMesh;

	UPROPERTY(EditAnywhere, Category = Item)
	class UTexture2D* InventoryImage;
	
	/*
	* item显示用文本
	*/
	UPROPERTY(EditAnywhere, Category = Item)
	FText PickupText;

	UPROPERTY(EditAnywhere, Category = Item)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class UPickupText> UMGClass;

	/*
	* item显示用文本控件
	*/
	UPROPERTY()
	class UPickupText* PickupTextWidget;

private:
	bool bIsInRange;
};
