// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARTS_Controller::ARTS_Controller()
{
	bReplicates = false;
}

void ARTS_Controller::BeginPlay()
{
	Super::BeginPlay();
}