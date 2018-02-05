// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"
#include "PrototypeCharacter.h"
#include "Components/SphereComponent.h"
#include "UMG/PickupText.h"


// Sets default values
AItemActor::AItemActor()
:UMGClass(nullptr)
{
	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerCollision"));
	if (TriggerCollision)
	{
		TriggerCollision->ShapeColor = FColor(0, 255, 0, 255);
		TriggerCollision->InitSphereRadius(300.0f);
		TriggerCollision->SetCollisionProfileName(TEXT("TriggerCollision"));
		TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::ComponentBeginOverlap);
		TriggerCollision->OnComponentEndOverlap.AddDynamic(this, &AItemActor::ComponentEndOverlap);
		RootComponent = TriggerCollision;
	}

	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	if (PreviewMesh)
	{
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PreviewMesh->SetupAttachment(RootComponent);
		PreviewMesh->SetRelativeScale3D(FVector(3, 3, 3));
	}

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AItemActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PickupTextWidget)
	{
		PickupTextWidget->PositionUpdate();
	}
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld && UMGClass != nullptr)
	{
		PickupTextWidget = CreateWidget<UPickupText>(CurrentWorld, UMGClass);
		PickupTextWidget->SetReferenceActor(this);
		PickupTextWidget->SetShowText(PickupText);

		APrototypeCharacter* Player = Cast<APrototypeCharacter>(UGameplayStatics::GetPlayerCharacter(CurrentWorld, 0));
		if (Player)
		{
			Player->OnPickupItem().AddUObject(this, &AItemActor::OnPickupItem);
		}
	}
}

void AItemActor::BeginDestroy()
{
	if (PickupTextWidget)
	{
		PickupTextWidget->SetReferenceActor(nullptr);
		PickupTextWidget->RemoveFromParent();
	}

	Super::BeginDestroy();
}

void AItemActor::OnPickupItem(class APrototypeCharacter* Player)
{
	if (!bIsInRange || !Player)
		return;

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	// 移掉场景里显示的UI
	if (PickupTextWidget)
	{
		PickupTextWidget->RemoveFromParent();
	}

	FPrototype_ItemInfor Item;
	Item.ItemType = ItemType;
	Item.ItemStat = EItemStat::Unequipped;
	Item.InventoryImage = InventoryImage;

	Player->CurrentItems.Add(Item);

	Player->RefreshInventory();
}

void AItemActor::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Other)
		return;

	APrototypeCharacter* Player = Cast<APrototypeCharacter>(Other);
	if (Player && PickupTextWidget)
	{
		bIsInRange = true;
		PickupTextWidget->AddToViewport();
	}
}

void AItemActor::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	APrototypeCharacter* Player = Cast<APrototypeCharacter>(OtherActor);
	if (Player && PickupTextWidget)
	{
		bIsInRange = false;
		PickupTextWidget->RemoveFromViewport();
	}
}

