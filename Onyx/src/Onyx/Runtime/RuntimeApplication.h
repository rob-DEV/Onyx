#ifndef _ONYX_RUNTIME_APPLICATION_H_
#define _ONYX_RUNTIME_APPLICATION_H_

#include <Onyx/Core/Application.h>

namespace Onyx {

	class ONYX_API RuntimeApplication : public Application
	{
	public:
		RuntimeApplication();
		~RuntimeApplication();

		void Run();

	};

}

#endif // !_ONYX_RUNTIME_APPLICATION_H_