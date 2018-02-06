#include "PrototypeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UMG/CharInforViewer.h"
#include "ItemActor.h"
#include "Components/StaticMeshComponent.h"

const static FName WeaponRight_SocketName = TEXT("Weapon_Right");
const static FName Shield_SocketName = TEXT("Weapon_Left");
const static FName Helmet_SocketName = TEXT("Helmet");

APrototypeCharacter::APrototypeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera									
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Weapon = NewObject<UStaticMeshComponent>(this, TEXT("Weapon"));
	Weapon->SetMobility(EComponentMobility::Movable);

	Shield = NewObject<UStaticMeshComponent>(this, TEXT("Shield"));
	Shield->SetMobility(EComponentMobility::Movable);

	Helmet = NewObject<UStaticMeshComponent>(this, TEXT("Helmet"));
	Helmet->SetMobility(EComponentMobility::Movable);

	if (GetMesh())
	{
		Weapon->SetupAttachment(GetMesh(), WeaponRight_SocketName);
		Weapon->SetRelativeLocation(FVector(0, 0, 60));
		Weapon->SetRelativeScale3D(FVector(3, 3, 3));
		Shield->SetupAttachment(GetMesh(), Shield_SocketName);
		Helmet->SetupAttachment(GetMesh(), Helmet_SocketName);	
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void APrototypeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APrototypeCharacter::Attack);

	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APrototypeCharacter::ToggleCharcterInforViewer);
	PlayerInputComponent->BindAction("PickupItem", IE_Pressed, this, &APrototypeCharacter::PickupItem);

	PlayerInputComponent->BindAxis("MoveForward", this, &APrototypeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APrototypeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APrototypeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APrototypeCharacter::LookUpAtRate);

}

void APrototypeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APrototypeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void APrototypeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APrototypeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void APrototypeCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld && ViewerUMGClass != nullptr)
	{
		CharacterInforViewer = CreateWidget<UCharInforViewer>(CurrentWorld, ViewerUMGClass);
	}
}

void APrototypeCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APrototypeCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APrototypeCharacter::Attack()
{

}

void APrototypeCharacter::ToggleCharcterInforViewer()
{
	if (!CharacterInforViewer)
		return;

	CharacterInforViewer->ToggleVisibility();
	CharacterInforViewer->RefreshInventory(CurrentItems);
}

void APrototypeCharacter::RefreshInventory()
{
	if (CharacterInforViewer)
	{
		CharacterInforViewer->RefreshInventory(CurrentItems);
	}

	// Attach item to Character mesh
	if (GetMesh())
	{
		for (const FPrototype_ItemInfor& Item : CurrentItems)
		{
			if (Item.ItemStat == EItemStat::Equipped
				&& Item.InventoryMesh)
			{
				if (Item.ItemType == EItemType::Weapon_1Handed)
				{
					Weapon->SetStaticMesh(Item.InventoryMesh);
				}
				else if (Item.ItemType == EItemType::Armor_Shield)
				{
					Shield->SetStaticMesh(Item.InventoryMesh);
				}
				else if (Item.ItemType == EItemType::Armor_Helmet)
				{
					Helmet->SetStaticMesh(Item.InventoryMesh);
				}
			}
		}
	}
}

void APrototypeCharacter::ItemUsed(class UItemComponent* Item)
{

}

void APrototypeCharacter::PickupItem()
{
	OnPickupItemDelegate.Broadcast(this);

	RefreshInventory();
}
