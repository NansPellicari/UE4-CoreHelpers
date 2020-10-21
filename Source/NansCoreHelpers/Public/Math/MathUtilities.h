#pragma once

#include "CoreMinimal.h"

#include "MathUtilities.generated.h"

#ifndef TOFLAG
#define TOFLAG(Enum) (1 << static_cast<uint8>(Enum))
#endif

/** This is relative to the zone, not the player */
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum ELateralityOrientation
{
	None = 0 UMETA(Hidden),
	Left = 0x00000001,
	Right = 0x00000002,
};

ENUM_CLASS_FLAGS(ELateralityOrientation)

UENUM(BlueprintType)
enum class EZoneCollider : uint8
{
	AABB UMETA(DisplayName = "Bounding Box"),
	AAB UMETA(DisplayName = "Box"),
	OBB UMETA(DisplayName = "Oriented Box"),
	Sphere UMETA(DisplayName = "Sphere"),
	SphereXY UMETA(DisplayName = "Sphere XY"),
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneBox|Settings")
	EZoneCollider CollideOn = EZoneCollider::SphereXY;

	FZoneBox();

	FZoneBox(FVector _Origin, FVector _Extent, FRotator _Rotation) : Origin(_Origin), Extent(_Extent), Rotation(_Rotation) {}

	/** Only returns the FBox (AAB) build with origin and extend */
	FBox GetBox() const;
	/** Returns the FBox (AABB) build with origin and extend + rotation */
	FBox GetBoundingBox() const;
	/** Returns the FOrientedBox (OBB) build with origin and extend + rotation */
	FOrientedBox GetOrientedBox() const;
	/** Returns the FSphere which wraps everything */
	FSphere GetSphere() const;
	/** Returns the FSphere inscribed (in the X & Y axis only) on the AAB box */
	FSphere GetSphereXY() const;
	bool Intersect(const FZoneBox& Other) const;
	bool Intersect(const FSphere& Other) const;
	bool Intersect(const FBox& Other) const;
	bool Intersect(const FOrientedBox& Other) const;
};

// 0: Left corner, 1: right corner
typedef TArray<FVector, TFixedAllocator<2>> TCorners;

class NANSCOREHELPERS_API NMathUtilities
{
public:
	static FVector GetClosestCorner(
		int32 SideToTest, const FZoneBox& Box, const TCorners& CornerData, ELateralityOrientation& Side, bool bDebug = false);

	// Thank to this https://answers.unity.com/questions/511841/how-to-make-an-object-move-away-from-three-or-more.html
	static FVector2D FindCentroid(const TArray<FVector2D> Positions);
};

/**
 *  this class is widely inspired by https://github.com/gszauer/GamePhysicsCookbook/blob/master/Code/Geometry3D.cpp
 */
class NANSCOREHELPERS_API NGeometry
{
public:
	static FOrientedBox CreateOrientedBox(const FBox& AABB, const FRotator& Rot);
	static bool Intersects(const FBox& AABB, const FOrientedBox& OBB);
	static bool Intersects(const FOrientedBox& OBB, const FSphere& Sphere);
	static bool Intersects(const FOrientedBox& OBB1, const FOrientedBox& OBB2);
	static bool OverlapOnAxis(const FOrientedBox& OBB1, const FOrientedBox& OBB2, const FVector& axis);
	static bool OverlapOnAxis(const FBox& AABB, const FOrientedBox& OBB, const FVector& axis);
	static FFloatInterval GetInterval(const FBox& AABB, const FVector& axis);
	static TArray<FVector> GetVertices(const FBox& AABB);
	static FVector ClosestPoint(const FOrientedBox& OBB, const FVector& Point);
};
