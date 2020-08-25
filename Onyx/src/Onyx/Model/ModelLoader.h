#ifndef _ONYX_MODEL_LOADER_H_
#define _ONYX_MODEL_LOADER_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Model/Model.h>
#include <Onyx/Graphics/Mesh.h>

namespace Onyx {

	class ONYX_API ModelLoader {
	public:
		static Model* LoadFromFile(const std::string& path);

	private:
		static Model* LoadObjFromFile(const std::string& path);
		static Model* LoadFbxFromFile(const std::string& path);

	};


}

#endif