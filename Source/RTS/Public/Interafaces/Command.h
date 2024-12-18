// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Command.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommand : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API ICommand
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveUnit(const FVector Location);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveDecal();
	
	virtual void MoveUnit_Implementation(const FVector Location) = 0;
	virtual void RemoveDecal_Implementation() = 0;
	
};
