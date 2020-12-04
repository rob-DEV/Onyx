#ifndef _ONYX_CORE_H_
#define _ONYX_CORE_H_

#include <stdint.h>

//--ONYX--EXPORTS--//
#ifdef _ONYX_BUILD_DLL_
#define ONYX_API __declspec(dllexport)
#else
#define ONYX_API __declspec(dllimport)
#endif

#define ONYX_LOG(log_msg) printf("%s\n", log_msg)
#define ONYX_ERROR(error_msg) {printf("%s\n", error_msg); assert(false); }

#endif // !_ONYX_CORE_H_