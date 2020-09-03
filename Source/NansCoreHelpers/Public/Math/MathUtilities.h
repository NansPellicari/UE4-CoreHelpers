#pragma once

#include "CoreMinimal.h"

#include "MathUtilities.generated.h"

#define TOFLAG(Enum) (1 << static_cast<uint8>(Enum))

/** This is relative to the zone, not the player */
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum ELateralityOrientation
{
	None = 0 UMETA(Hidden),
	Left = 0x00000001,
	Right = 0x00000002,
};

ENUM_CLASS_FLAGS(ELateralityOrientation)

USTRUCT(BlueprintType)
struct NANSCOREHELPERS_API FZoneBox
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FVector Extent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	FRotator Rotation;

	FZoneBox();

	FZoneBox(FVector _Origin, FVector _Extent, FRotator _Rotation) : Origin(_Origin), Extent(_Extent), Rotation(_Rotation) {}

	FBox GetBox() const;
	FSphere GetSphere() const;
	FSphere GetSphereXY() const;
	bool Intersect(const FZoneBox& Other) const;
};

// 0: Left corner, 1: right corner
typedef TArray<FVector, TFixedAllocator<2>> TCorners;

class NANSCOREHELPERS_API NMathUtilities
{
public:
	static FVector GetClosestCorner(
		int32 SideToTest, const FZoneBox& Box, const TCorners& CornerData, ELateralityOrientation& Side, bool bDebug = false);
};
