#ifndef _ONYX_SCRIPTING_SCRIPT_H_
#define _ONYX_SCRIPTING_SCRIPT_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

namespace Onyx {

	class NativeScript
	{
	public:
		virtual ~NativeScript() {}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	};
}

#endif
