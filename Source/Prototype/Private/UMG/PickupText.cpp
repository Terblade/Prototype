#include "UMG/PickupText.h"

void UPickupText::PositionUpdate()
{
	if (!GetReferenceActor())
		return;

	UWorld* CurrentWorld = GetReferenceActor()->GetWorld();
	if (!CurrentWorld)
		return;

	APlayerController* PlayerCtr = UGameplayStatics::GetPlayerController(CurrentWorld, 0);
	if (!PlayerCtr)
		return;

	FVector WorldPosition = GetReferenceActor()->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
	FVector2D ScreenSpacePosition;
	bool bProjectSuccessful = PlayerCtr->ProjectWorldLocationToScreen(WorldPosition, ScreenSpacePosition);

	if (bProjectSuccessful)
	{
		SetVisibility(ESlateVisibility::Visible);
		SetPositionInViewport(ScreenSpacePosition);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

//UPickupText::UPickupText()
//{
//	
//}

void UPickupText::SetReferenceActor(class AActor* InActor)
{
	ReferenceActor = InActor;
}

void UPickupText::SetShowText(const FText& InText)
{
	ShowText = InText;
}

void UPickupText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
