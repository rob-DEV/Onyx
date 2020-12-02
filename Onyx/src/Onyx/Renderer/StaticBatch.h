#ifndef _ONYX_RENDERER_STATIC_BATCH_
#define _ONYX_RENDERER_STATIC_BATCH_

#include "CommonMaterialBuffer.h"

namespace Onyx {

	class StaticBatch {
	public:

		StaticBatch();
		~StaticBatch();

		void Begin();

		void SetBufferLayout(const BufferLayout& bufferLayout) { m_BufferLayout = bufferLayout; };
		void Submit(uint32_t id, const std::vector<Mesh>& meshes, const glm::mat4& transform);

		void End();

		bool IsInBatch(uint32_t id);


	private:
		std::vector<uint32_t> m_EnititiesInBatch;
		std::unordered_map <std::string, CommonMaterialBuffer*> m_CommonMaterialBuffers;
		BufferLayout m_BufferLayout;
		static const uint32_t MAX_ENTITIES_IN_BATCH = 1000;

	};

}

#endif // !_ONYX_RENDERER_STATIC_BATCH_
