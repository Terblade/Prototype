#include "ItemComponent.h"
#include "PrototypeCharacter.h"
#include "Components/SphereComponent.h"
#include "UMG/PickupText.h"

UItemComponent::UItemComponent()
{
	bIsInRange = false;
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	if (PreviewMesh)
	{
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerCollision"));
	if (TriggerCollision)
	{
		TriggerCollision->ShapeColor = FColor(0, 255, 0, 255);
		TriggerCollision->InitSphereRadius(300.0f);
		TriggerCollision->SetCollisionProfileName(TEXT("TriggerCollision"));
		TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &UItemComponent::ComponentBeginOverlap);
		TriggerCollision->OnComponentEndOverlap.AddDynamic(this, &UItemComponent::ComponentEndOverlap);
	}

	//PickupTextWidget = CreateWidget<UPickupText>(GetOwningPlayer());
}

void UItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UItemComponent::OnPickupItem(APrototypeCharacter* Player)
{
	if (!bIsInRange || !Player)
		return;

	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(true);
		GetOwner()->SetActorEnableCollision(false);
	}

	// 移掉场景里显示的UI
	if (PickupTextWidget)
	{
		PickupTextWidget->RemoveFromParent();
	}
	
	Player->CurrentItems.AddUnique(this);
	Player->RefreshInventory();
}

void UItemComponent::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Other)
		return;

	APrototypeCharacter* Player = Cast<APrototypeCharacter>(Other);
	if (Player)
	{
		bIsInRange = true;
		PickupTextWidget->AddToViewport();
	}
}

void UItemComponent::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	APrototypeCharacter* Player = Cast<APrototypeCharacter>(OtherActor);
	if (Player)
	{
		bIsInRange = false;
		PickupTextWidget->RemoveFromViewport();
	}


}

