#pragma once

#include "CoreMinimal.h"

#include "MathTypes.generated.h"

USTRUCT(BlueprintType)
struct FRange
{
	GENERATED_USTRUCT_BODY()

public:
	FRange() {}
	FRange(float _Lh, float _Rh) : Lh(_Lh), Rh(_Rh) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float Lh = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float Rh = 100;
};
