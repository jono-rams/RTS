// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_Controller.h"

ARTS_Controller::ARTS_Controller()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
}

FVector ARTS_Controller::GetMouseLocation() const
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	return HitResult.Location;
}

void ARTS_Controller::BeginPlay()
{
	Super::BeginPlay();
}
