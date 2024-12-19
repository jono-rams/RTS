// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/TimeState.h"
#include "GameFramework/Character.h"
#include "RTS_Character.generated.h"

struct FInputActionValue;
class UInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RTS_API ARTS_Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Input", meta = (AllowPrivateAccess = "true"))
	float ScrollAmount;

	UPROPERTY(EditDefaultsOnly, Category="Camera|Input", meta = (AllowPrivateAccess = "true"))
	FVector DefaultCameraLocation;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	float MinMoveSpeed;

	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	float MouseSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	bool InvertMouseX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	bool InvertMouseY;
	
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem; 

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ScrollAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ResetZoomAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> RightClickAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LeftClickAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gameplay", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> Units;

public:
	// Sets default values for this character's properties
	ARTS_Character();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputActionValue);
	
	void Scroll(const FInputActionValue& InputActionValue);

	void ResetZoom(const FInputActionValue& InputActionValue);

	void HandleRightClick(const FInputActionValue& InputActionValue);

	void HandleLeftClick(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable)
	void RotateX(float MouseX);

	UFUNCTION(BlueprintCallable)
	void RotateY(float MouseY);

	UFUNCTION(BlueprintCallable)
	void UpdateTimeState(ETimeState CurrentTimeState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateSpeed() const;

	void UpdateCameraRelativeLocation(const FVector& NewLocation) const;

	FORCEINLINE bool CanRotate() const;

public:
	FORCEINLINE TArray<AActor*> GetUnits() const { return Units; }
	FORCEINLINE AActor* GetUnitByIndex(const int Index) const { return Units[Index]; }
	FORCEINLINE void AddUnit(AActor* Unit) { Units.AddUnique(Unit); }
};
