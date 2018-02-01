#pragma once
#include "CoreMinimal.h"
#include "ItemComponent.generated.h"

UCLASS(config = Game, Meta = (BlueprintSpawnableComponent), ClassGroup = (Gameplay, Item))
class UItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UItemComponent();

	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	// end UActorComponent interface

	//
	void OnPickupItem(class APrototypeCharacter* Player);

	/* Delegates */
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///* Delegates */
	UFUNCTION()
	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, Category = Item)
	class UTexture2D* InventoryImage;

	/*
	* 预览模型
	*/
	UPROPERTY(EditAnywhere, Category = Item)
	class UStaticMeshComponent* PreviewMesh;

	/*
	* item显示用文本
	*/
	UPROPERTY(EditAnywhere, Category = Item)
	FText PickupText;

	/*
	* item显示用文本控件
	*/
	UPROPERTY()
	class UUserWidget* PickupTextWidget;

	/** Sphere component used for collision */
	UPROPERTY(BlueprintReadOnly)
	class USphereComponent* TriggerCollision;

private:
	bool bIsInRange;
};