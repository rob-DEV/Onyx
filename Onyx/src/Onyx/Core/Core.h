#ifndef _ONYX_CORE_H_
#define _ONYX_CORE_H_

#ifdef _ONYX_BUILD_DLL_
#define ONYX_API __declspec(dllexport)
#else
#define ONYX_API __declspec(dllimport)
#endif


#endif // !_ONYX_CORE_H_