#ifndef _ONYX_EDITOR_SCENE_H_
#define _ONYX_EDITOR_SCENE_H_


namespace Onyx {

	class SceneEditorSelector
	{
	public:
		inline static uint32_t GetSelectedEntity() { return s_SelectedEntity; };
	private:
		static uint32_t s_SelectedEntity;
	};

}

#endif