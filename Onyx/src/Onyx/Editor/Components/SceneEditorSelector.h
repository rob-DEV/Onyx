#ifndef _ONYX_EDITOR_SCENE_ENTITY_SELECTOR_H_
#define _ONYX_EDITOR_SCENE_ENTITY_SELECTOR_H_


namespace Onyx {


	class SceneEditorSelector
	{
	public:
		static uint32_t GetSelectedEntityId() {
			return s_SelectedEntity;
		}

		static void SetSelectedEntityId(uint32_t entityID) {
			s_SelectedEntity = entityID;
		}
	private:
		inline static uint32_t s_SelectedEntity = 0x00FFFFFF;
	};

}

#endif