#ifndef _ONYX_EDITOR_SCENE_SERIALIZER_H_
#define _ONYX_EDITOR_SCENE_SERIALIZER_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Scene/Scene.h>

namespace Onyx {

	class ONYX_API SceneSerializer {
	public:
		static bool Serialize(Scene* scene, std::string_view filePath);

		static Scene* DeSerialize(std::string_view filePath);

	};

}

#endif // !_ONYX_EDITOR_SCENE_SERIALIZER_H_