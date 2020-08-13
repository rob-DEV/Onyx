#ifndef _ONYX_TIMESTEP_H_
#define _ONYX_TIMESTEP_H_

#include <Onyx/Core/Core.h>

namespace Onyx {

	class ONYX_API TimeStep {

	public:

		TimeStep(float time) 
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; };

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};



}


#endif