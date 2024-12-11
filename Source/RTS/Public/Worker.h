// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Worker.generated.h"

UCLASS()
class RTS_API AWorker : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	UAnimMontage* IntroMontage;

public:
	// Sets default values for this character's properties
	AWorker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
