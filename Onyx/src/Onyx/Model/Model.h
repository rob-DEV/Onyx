#ifndef _ONYX_MODEL_H_
#define _ONYX_MODEL_H_

#include <Onyx/Graphics/Mesh.h>

namespace Onyx {
	class Model
	{
	public:
		std::vector<Mesh*> m_Meshes;
	
	private:
		friend class ModelLoader;
	};
}

#endif

