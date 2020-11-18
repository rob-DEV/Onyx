#include "onyxpch.h"
#include "Console.h"

namespace Onyx {

	void Console::CreateDebug()
	{
		#if defined(_ONYX_BUILD_TARGET_WINDOWS_) && defined(_ONYX_DEBUG_)
		
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		#endif // _ONYX_BUILD_TARGET_WINDOWS_
	}

}