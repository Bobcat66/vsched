#pragma once

#ifdef _MSC_VER
#define VS_ASSUME(x) __assume(x)
#define VS_EXPECT(x) (x)
#define VS_UNEXPECT(x) (x)
#endif // _MSC_VER

#ifdef __GNUC__
#define VS_ASSUME(x) do { if (!(x)) __builtin_unreachable(); } while (0)
#define VS_EXPECT(x) __builtin_expect(!!(x),1)
#define VS_UNEXPECT(x) __builtin_expect(!!(x),0)
#endif // __GNUC__