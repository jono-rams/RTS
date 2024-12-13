// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Controller.h"

ARTS_Controller::ARTS_Controller()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
}

void ARTS_Controller::BeginPlay()
{
	Super::BeginPlay();
}