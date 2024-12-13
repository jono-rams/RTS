// Fill out your copyright notice in the Description page of Project Settings.


#include "Worker.h"

#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("b_MF_Weapon_L"));
	Weapon->SetVisibility(false);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(GetRootComponent());
	Decal->SetVisibility(false);
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();

	if (IntroMontage) PlayAnimMontage(IntroMontage);

	Weapon->SetVisibility(true);
}

// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWorker::HandleActorClicked() const
{
	Decal->SetVisibility(true);
}


