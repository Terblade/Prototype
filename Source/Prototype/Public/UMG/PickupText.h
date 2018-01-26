#pragma once

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "PickupText.generated.h"

UCLASS()
class UPickupText : public UUserWidget
{
	GENERATED_BODY()

public:
	//UPickupText();
	
	//UFUNCTION(BlueprintCallable, Category = "PickupText")
	/*
	* 依赖上层去调用这个函数， nativetick在ui跑出viewport以后会自动优化停止.
	*/
	void PositionUpdate();

	/*
	* Reference Actor Get/Set
	*/
	FORCEINLINE class AActor* GetReferenceActor() const;
	void SetReferenceActor(class AActor* InComponent);

	/*
	* ShowText Get/Set
	*/
	FORCEINLINE const class FText& GetShowText() const;
	void SetShowText(const FText& InText);

protected:
	// Begin UUserWidget interface
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// end UUserWidget interface
private:
	/*
	* Bind to UMG text block
	*/
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FText ShowText;

	class AActor* ReferenceActor;
};

FORCEINLINE class AActor* UPickupText::GetReferenceActor() const
{
	return ReferenceActor;
}

FORCEINLINE const class FText& UPickupText::GetShowText() const
{
	return ShowText;
}