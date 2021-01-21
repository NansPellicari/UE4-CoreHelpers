#include "CoreMinimal.h"
#include "gtest/gtest.h"
#include "NansCoreHelpers/Public/Math/MathUtilities.h"

#include <iostream>

class GeometryTest : public ::testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	bool bDebug = false;
};

TEST_F(GeometryTest, TestUnionOnIntersectOn2Shapes)
{
	FIntRect Rect1, Rect2;
	FIntRect UnionRect;

	// - 0 0
	// 1 1 -
	Rect1 = FIntRect(
		FIntPoint(1, 0),
		FIntPoint(3, 1)
	);
	Rect2 = FIntRect(
		FIntPoint(0, 1),
		FIntPoint(2, 2)
	);

	UnionRect = NGeometry::UnionOnIntersect(Rect1, Rect2);
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 2));

	// 0 0 -
	// - 1 1
	Rect1 = FIntRect(
		FIntPoint(0, 0),
		FIntPoint(2, 1)
	);
	Rect2 = FIntRect(
		FIntPoint(1, 1),
		FIntPoint(3, 2)
	);

	UnionRect = NGeometry::UnionOnIntersect(Rect1, Rect2);
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 2));

	// 0 0
	// 1 1
	Rect1 = FIntRect(
		FIntPoint(0, 0),
		FIntPoint(2, 1)
	);
	Rect2 = FIntRect(
		FIntPoint(0, 1),
		FIntPoint(2, 2)
	);

	UnionRect = NGeometry::UnionOnIntersect(Rect1, Rect2);
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 2));

	// 0 -
	// 0 1
	// - 1
	Rect1 = FIntRect(
		FIntPoint(0, 0),
		FIntPoint(1, 2)
	);
	Rect2 = FIntRect(
		FIntPoint(1, 1),
		FIntPoint(2, 3)
	);

	UnionRect = NGeometry::UnionOnIntersect(Rect1, Rect2);
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 1));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 2));

	// 0 0 0
	// - 1 1
	Rect1 = FIntRect(
		FIntPoint(0, 0),
		FIntPoint(3, 1)
	);
	Rect2 = FIntRect(
		FIntPoint(1, 1),
		FIntPoint(3, 2)
	);

	UnionRect = NGeometry::UnionOnIntersect(Rect1, Rect2);
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(3, 2));
}

TEST_F(GeometryTest, TestUnionOnIntersectOn3Shapes)
{
	TArray<FIntRect> Rects;
	FIntRect UnionRect;

	// | 0 0 2 |
	// |   1 2 |
	// |     2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(1, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(2, 0),
			FIntPoint(3, 3)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(3, 2));

	// | 0 1 1 2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(1, 1)
		),
		FIntRect(
			FIntPoint(1, 0),
			FIntPoint(3, 1)
		),
		FIntRect(
			FIntPoint(3, 0),
			FIntPoint(4, 1)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(4, 1));

	// |   1 |
	// | 0 0 |
	// |   2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(1, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(1, 2),
			FIntPoint(2, 3)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 3));

	// | 0 2 | 
	// | 1 1 |
	Rects = {
		FIntRect(
			FIntPoint(0, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(1, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(1, 1)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 2));

	// | 0 0 |
	// |   1 |
	// |   2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(1, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(1, 2),
			FIntPoint(2, 3)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(1, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 3));

	// | 0 0   |
	// |   1 2 |
	// |     2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(1, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(2, 1),
			FIntPoint(3, 3)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(2, 1));

	// | 0 1 1 2 |
	// |   1 1   |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(1, 1)
		),
		FIntRect(
			FIntPoint(1, 0),
			FIntPoint(3, 2)
		),
		FIntRect(
			FIntPoint(3, 0),
			FIntPoint(4, 1)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(4, 1));

	// | 0   2 |
	// | 0 1 2 |
	// |     2 |
	Rects = {
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(1, 2)
		),
		FIntRect(
			FIntPoint(1, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(2, 0),
			FIntPoint(3, 3)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 1));
	ASSERT_EQ(UnionRect.Max, FIntPoint(3, 2));
}

TEST_F(GeometryTest, TestUnionOnIntersectOn4Shapes)
{
	TArray<FIntRect> Rects;
	FIntRect UnionRect;

	// | 0 2 3 | 
	// | 1 1 3 |
	Rects = {
		FIntRect(
			FIntPoint(0, 1),
			FIntPoint(2, 2)
		),
		FIntRect(
			FIntPoint(1, 0),
			FIntPoint(2, 1)
		),
		FIntRect(
			FIntPoint(0, 0),
			FIntPoint(1, 1)
		),
		FIntRect(
			FIntPoint(2, 0),
			FIntPoint(3, 2)
		)
	};

	if (bDebug) std::cout << "------------\nNew Test:\n";
	UnionRect = NGeometry::UnionOnIntersect(Rects, bDebug);
	if (bDebug) std::cout << "UnionRect " << ": " << TCHAR_TO_ANSI(*UnionRect.ToString()) << "\n";
	ASSERT_EQ(UnionRect.Min, FIntPoint(0, 0));
	ASSERT_EQ(UnionRect.Max, FIntPoint(3, 2));
}
