#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class ETimeState : uint8 
{
	Pause  UMETA(DisplayName = "Pause"), 
	Slow  UMETA(DisplayName = "Slow"),
	Normal  UMETA(DisplayName = "Normal"),
	Fast  UMETA(DisplayName = "Fast"),
	SuperFast UMETA(DisplayName = "Super Fast")
};