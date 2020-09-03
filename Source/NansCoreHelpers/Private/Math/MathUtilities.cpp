#include "Math/MathUtilities.h"

FZoneBox::FZoneBox()
{
	Origin = FVector::ZeroVector;
	Extent = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
}

FBox FZoneBox::GetBox() const
{
	// return UMathExtensionLibrary::CreateBoxFromInitAndExtend(Origin, Extent, FRotator::ZeroRotator);
	return FBox(Origin - Extent, Origin + Extent);
}

FSphere FZoneBox::GetSphere() const
{
	float W = (Origin - (Origin + Extent)).Size();
	FSphere Sphere(Origin, W);

	return Sphere;
}
FSphere FZoneBox::GetSphereXY() const
{
	FVector OToE = Origin + FVector(Extent.X, Extent.Y, 0);
	FVector OToEOpposite = Origin - FVector(-Extent.X, Extent.Y, 0);
	FVector MiddlePoint = (OToEOpposite + OToE) / 2;
	float W = (Origin - MiddlePoint).Size();
	FSphere Sphere(Origin, W);
	return Sphere;
}

bool FZoneBox::Intersect(const FZoneBox& Other) const
{
	bool bIsIntersect = false;
	if (GetBox().Intersect(Other.GetBox()))
	{
		bIsIntersect = GetSphereXY().Intersects(Other.GetSphereXY());
	}

	return bIsIntersect;
}

FVector NMathUtilities::GetClosestCorner(
	int32 SideToTest, const FZoneBox& Box, const TCorners& CornerData, ELateralityOrientation& Side, bool bDebug)
{
	FVector ClosestCorner;

	if (SideToTest & ELateralityOrientation::Left && SideToTest & ELateralityOrientation::Right)
	{
		float LeftDist = (Box.Origin - CornerData[0]).Size();
		float RightDist = (Box.Origin - CornerData[1]).Size();
		Side = LeftDist < RightDist ? ELateralityOrientation::Left : ELateralityOrientation::Right;
		ClosestCorner = LeftDist < RightDist ? CornerData[0] : CornerData[1];
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s - corner on  both"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	else if (SideToTest & ELateralityOrientation::Left)
	{
		ClosestCorner = CornerData[0];
		Side = ELateralityOrientation::Left;
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s - corner on left"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	else
	{
		ClosestCorner = CornerData[1];
		Side = ELateralityOrientation::Right;
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s - corner on right"), ANSI_TO_TCHAR(__FUNCTION__));
	}
	return ClosestCorner;
};
