#include "UMG/PickupText.h"

FVector UPickupText::GetShowPosition()
{	
	return ReferenceActor ? ReferenceActor->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f) : FVector::ZeroVector;
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
