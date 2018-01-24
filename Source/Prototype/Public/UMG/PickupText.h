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
	UFUNCTION(BlueprintImplementableEvent)
	void OnTextChanged(FText& InText);

	FORCEINLINE class UActorComponent* GetReferenceComponent() const;
	void SetReferenceComponent(class UActorComponent* InComponent);
private:
	class UActorComponent* ReferenceComponent;
};

FORCEINLINE class UActorComponent* UPickupText::GetReferenceComponent() const
{
	return ReferenceComponent;
}