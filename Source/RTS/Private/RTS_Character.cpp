// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Character.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RTS_Controller.h"
#include "RTS_LevelScriptActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Interafaces/Command.h"
#include "Nodes/InterchangeBaseNode.h"

// Sets default values
ARTS_Character::ARTS_Character() :
	ScrollAmount(10.f),
	MinMoveSpeed(150.f),
	MouseSensitivity(4.f),
	InvertMouseX(false),
	InvertMouseY(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ARTS_Character::BeginPlay()
{
	Super::BeginPlay();
	check(MappingContext);
	DefaultCameraLocation = Camera->GetRelativeLocation();
	UpdateSpeed();
}

void ARTS_Character::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetController<APlayerController>()->GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ARTS_Character::Scroll(const FInputActionValue& InputActionValue)
{
	const float ScrollValue = InputActionValue.Get<float>();
	const FVector CameraLoc = Camera->GetRelativeLocation();
	const FVector NewCameraLocation = FVector(CameraLoc.X + (ScrollValue * ScrollAmount), CameraLoc.Y, CameraLoc.Z);

	UpdateCameraRelativeLocation(NewCameraLocation);
}

void ARTS_Character::ResetZoom(const FInputActionValue& InputActionValue)
{
	UpdateCameraRelativeLocation(DefaultCameraLocation);
}

void ARTS_Character::HandleRightClick(const FInputActionValue& InputActionValue)
{
	if (Units.IsEmpty()) return;
	
	const FVector MouseLocation = Cast<ARTS_Controller>(GetController())->GetMouseLocation();
	for (const auto& Unit : Units)
	{
		if (const ICommand* CommandInterface = Cast<ICommand>(Unit))
		{
			CommandInterface->Execute_MoveUnit(Unit, MouseLocation);
		}
	}
}

void ARTS_Character::HandleLeftClick(const FInputActionValue& InputActionValue)
{
	if (Units.IsEmpty()) return;

	for (const auto& Unit : Units)
	{
		if (const ICommand* CommandInterface = Cast<ICommand>(Unit))
		{
			CommandInterface->Execute_RemoveDecal(Unit);
		}
	}
	Units.Empty();
}

void ARTS_Character::RotateX(const float MouseX)
{
	if (!CanRotate()) return;

	float Value = MouseX * MouseSensitivity;
	if (InvertMouseX) Value *= -1.f;

	AddControllerYawInput(Value);
}

void ARTS_Character::RotateY(const float MouseY)
{
	if (!CanRotate()) return;

	float Value = MouseY * MouseSensitivity;
	if (InvertMouseY) Value *= -1.f;
	
	CameraBoom->AddLocalRotation(FRotator(Value, 0.f, 0.f));
}

void ARTS_Character::UpdateTimeState(ETimeState CurrentTimeState)
{
	if (const auto LevelScriptActor = Cast<ARTS_LevelScriptActor>(GetWorld()->GetLevelScriptActor()))
	{
		if (const auto TimeInterface = Cast<ITime>(LevelScriptActor))
			TimeInterface->Execute_ChangeTimeState(LevelScriptActor, CurrentTimeState);
	}	
}

// Called every frame
void ARTS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast to EnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Get the Enhanced Input subsystem
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetController<APlayerController>()->GetLocalPlayer()); 

		// Ensure the Input Mapping Context is active
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(MappingContext, 0); // Replace YourInputMappingContext
		}

		// Bind input actions
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARTS_Character::Move);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ARTS_Character::Scroll);
		EnhancedInputComponent->BindAction(ResetZoomAction, ETriggerEvent::Completed, this, &ARTS_Character::ResetZoom);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ARTS_Character::HandleRightClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &ARTS_Character::HandleLeftClick);
	}
}

void ARTS_Character::UpdateSpeed() const
{
	const FVector CameraLoc = Camera->GetRelativeLocation();
	const float NewWalkSpeed = CameraLoc.X * -2.f;
	GetCharacterMovement()->MaxWalkSpeed = NewWalkSpeed > MinMoveSpeed ? NewWalkSpeed : MinMoveSpeed;
	// Print the new walk speed to the log
	UE_LOG(LogTemp, Display, TEXT("Walk Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
}

void ARTS_Character::UpdateCameraRelativeLocation(const FVector& NewLocation) const
{
	Camera->SetRelativeLocation(NewLocation);
	UpdateSpeed(); // Update character's speed based on camera's distance from player
}

bool ARTS_Character::CanRotate() const
{
	return Cast<APlayerController>(GetController())->IsInputKeyDown(EKeys::MiddleMouseButton);
}
