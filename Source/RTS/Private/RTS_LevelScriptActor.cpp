// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "Enums/TimeState.h"
#include "GameFramework/Character.h"

void ARTS_LevelScriptActor::SetGlobalTimeDilation(const UGameInstance* GameInstance, const float NewTimeDilation)
{
	GameInstance->GetWorld()->GetWorldSettings()->SetTimeDilation(NewTimeDilation);
}

ARTS_LevelScriptActor::ARTS_LevelScriptActor() :
	PauseTimeDilation(0.001f), SlowTimeDilation(0.5f), FastTimeDilation(2.f), SuperFastDilation(5.f),
	DaySpeed(1.f)
{
}

void ARTS_LevelScriptActor::ChangeTimeState_Implementation(ETimeState CurrentTimeState)
{
#include "Kismet/GameplayStatics.h" // Make sure to include this header

	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		if (const auto Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			switch (CurrentTimeState)
			{
			case ETimeState::Pause:
				SetGlobalTimeDilation(GameInstance, PauseTimeDilation);
				Character->CustomTimeDilation = 1.f / PauseTimeDilation;
				DaySpeed = PauseTimeDilation;
				break;
			case ETimeState::Slow:
				SetGlobalTimeDilation(GameInstance, SlowTimeDilation);
				Character->CustomTimeDilation = 1.f / SlowTimeDilation;
				DaySpeed = SlowTimeDilation;
				break;
			default:
			case ETimeState::Normal:
				SetGlobalTimeDilation(GameInstance, 1.0f);
				Character->CustomTimeDilation = 1.f;
				DaySpeed = 1.f;
				break;
			case ETimeState::Fast:
				SetGlobalTimeDilation(GameInstance, FastTimeDilation);
				Character->CustomTimeDilation = 1.f / FastTimeDilation;
				DaySpeed = FastTimeDilation;
				break;
			case ETimeState::SuperFast:
				SetGlobalTimeDilation(GameInstance, SuperFastDilation);
				Character->CustomTimeDilation = 1.f / SuperFastDilation;
				DaySpeed = SuperFastDilation;
				break;
			}
		}
	}
}

void ARTS_LevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateDirectionalLight(FRotator(DaySpeed * DeltaSeconds, 0.f, 0.f));
}
