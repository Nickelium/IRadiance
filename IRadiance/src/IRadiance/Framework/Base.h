#pragma once
// MACROS & STUFF
//#ifdef IRADPLATFORM_WINDOWS
//	#ifdef IRAD_EXPORT
//		#define IRADAPI __declspec(dllexport)
//	#else
//		#define IRADAPI __declspec(dllimport)
//	#endif
//#else
//	#error IRadiance currently only support Windows
//#endif


#ifdef IRAD_DEBUG
	#define IRAD_ENABLE_ASSERTS
#endif

#ifdef IRAD_ENABLE_ASSERTS
#define IRADASSERT(x, ...) { if(!(x)) { IRAD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define IRAD_CORE_ASSERT(x, ...) { if(!(x)) { IRAD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define IRADASSERT(x, ...)
#define IRAD_CORE_ASSERT(x, ...)
#endif

//#define BIND_FN(Func) [&](auto& _param){ return Func(_param);}
#define BIND_FN(Func) std::bind(&Func, this, std::placeholders::_1)
#define BIND_FN0(Func) std::bind(&Func, this)

#define BIT(X) (1 << X)

#include <stdint.h>
using Handle = uint32_t;