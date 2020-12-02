#ifndef _ONYX_RENDERER_COMMON_BUFFER_
#define _ONYX_RENDERER_COMMON_BUFFER_

#include <Onyx/Graphics/Mesh.h>
#include <Onyx/Graphics/Material.h>
#include <Onyx/Graphics/VertexArray.h>

namespace Onyx {

	struct EditorVertex3D {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec4 EntityIdentifier;
	};
	class CommonMaterialBuffer
	{
	public:


		CommonMaterialBuffer() = default;
		CommonMaterialBuffer(Material * material, const BufferLayout& bufferLayout);
		~CommonMaterialBuffer();

		void Begin();
		void Submit(uint32_t id, Mesh& mesh, glm::mat4 transform);
		void End();

	private:
		Material* m_Material;

		VertexArray* m_MeshVertexArray = nullptr;
		VertexBuffer* m_MeshVertexBuffer = nullptr;
		IndexBuffer* m_MeshIndexBuffer = nullptr;

		void* m_MeshVertexBufferBase = nullptr;
		void* m_MeshVertexBufferWritePtr = nullptr;

		uint32_t* m_MeshIndexBufferBase = nullptr;
		uint32_t* m_MeshIndexBufferWritePtr = nullptr;


		uint32_t m_IndexCount = 0;
		uint32_t m_VertexCount = 0;

		uint32_t m_MeshCountInBuffer = 0;
	};

}

#endif // !_ONYX_RENDERER_COMMON_BUFFER_
