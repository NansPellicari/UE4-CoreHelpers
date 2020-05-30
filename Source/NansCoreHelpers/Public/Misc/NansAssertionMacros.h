#pragma once

#include "CoreMinimal.h"

#if WITH_DEV_AUTOMATION_TESTS || defined WITH_GG_TESTS

extern NANSCOREHELPERS_API bool GNAssertThrowError;

#define mycheck(expr)          \
	{                          \
		if (UNLIKELY(!(expr))) \
		{                      \
			throw TEXT(#expr); \
		}                      \
	}
#define mycheckf(expr, format, ...) AssertHelpers::LogAndThrow(!!(expr), TEXT(#expr), format, ##__VA_ARGS__)

#define myensureMsgf(InExpression, InFormat, ...) \
	(AssertHelpers::LogAndThrow(!!(InExpression), TEXT(#InExpression), InFormat, ##__VA_ARGS__))

namespace AssertHelpers
{
	template <typename ExprType, typename FmtType, typename... Types>
	inline bool LogAndThrow(const bool Result, const ExprType& Expr, const FmtType& Format, Types... Args)
	{
		if (!Result)
		{
			UE_LOG(LogTemp, Display, Format, Args...);
			if (GNAssertThrowError) throw Expr;
		}
		return Result;
	}
}	 // namespace AssertHelpers
#else
#define mycheck(expr) check(expr)
#define mycheckf(expr, format, ...) checkf(expr, format, ##__VA_ARGS__)
#define myensureMsgf(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, ##__VA_ARGS__)
#endif
