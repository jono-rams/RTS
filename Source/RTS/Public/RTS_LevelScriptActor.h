// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Interafaces/Time.h"
#include "RTS_LevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTS_LevelScriptActor : public ALevelScriptActor, public ITime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Time, meta=(AllowPrivateAccess="true"))
	float PauseTimeDilation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta=(AllowPrivateAccess="true"))
	float SlowTimeDilation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta=(AllowPrivateAccess="true"))
	float FastTimeDilation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta=(AllowPrivateAccess="true"))
	float SuperFastDilation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNightCycle", meta=(AllowPrivateAccess="true"))
	float DaySpeed;

	static void SetGlobalTimeDilation(const UGameInstance* GameInstance, const float NewTimeDilation);

public:
	ARTS_LevelScriptActor();
	
	virtual void ChangeTimeState_Implementation(ETimeState CurrentTimeState) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDirectionalLight(FRotator Rotation);
};
