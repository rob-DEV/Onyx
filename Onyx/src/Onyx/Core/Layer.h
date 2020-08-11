#ifndef _ONYX_LAYER_H_
#define _ONYX_LAYER_H_

#include <Onyx/Core/Core.h>
#include <string>

namespace Onyx {

	class ONYX_API Layer {

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		const std::string& GetName() const { return m_LayerName; }

	protected:
		std::string m_LayerName;
	};


}


#endif