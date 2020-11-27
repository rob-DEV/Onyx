#ifndef _ONYX_RENDERER3D_H_
#define _ONYX_RENDERER3D_H_

#include <Onyx/Camera/Camera.h>
#include <Onyx/Graphics/Shader.h>

#include <Onyx/Graphics/Material.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/Framebuffer.h>

#include <Onyx/Graphics/ModelLoader.h>
#include <Onyx/Graphics/RenderCommand.h>


#include <unordered_map>

namespace Onyx {

	class Scene;
	class Model;

	class CommonMaterialBuffer {
	public:
		

		CommonMaterialBuffer() = default;
		CommonMaterialBuffer(Material* material);

		inline void Begin() {
			m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
			m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;

			m_IndexCount = 0;
			m_VertexCount = 0;
		}
		inline void Submit(const Mesh& mesh, glm::mat4 transform) {
			for (size_t i = 0; i < mesh.m_Vertices.size(); ++i) {

				memcpy(m_MeshVertexBufferWritePtr, &mesh.m_Vertices[i], sizeof(Vertex3D));
				((Vertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
				m_MeshVertexBufferWritePtr = (char*)m_MeshVertexBufferWritePtr + sizeof(Vertex3D);
			}

			for (size_t i = 0; i < mesh.m_Indices.size(); ++i) {

				*m_MeshIndexBufferWritePtr = mesh.m_Indices[i] + m_VertexCount;
				m_MeshIndexBufferWritePtr++;

			}

			m_IndexCount += mesh.m_Indices.size();
			m_VertexCount += mesh.m_Vertices.size();
			++m_MeshCountInBuffer;

		}

		inline void End() {
			m_MeshVertexArray->Bind();
			m_MeshIndexBuffer->Bind();
			m_MeshVertexBuffer->Bind();

			m_Material->Bind();

			unsigned long long vertexBufferSize = (unsigned char*)m_MeshVertexBufferWritePtr - (unsigned char*)m_MeshVertexBufferBase;

			if (vertexBufferSize != 0) {
				//set vertex buffer to draw
				m_MeshVertexBuffer->SetData((void*)m_MeshVertexBufferBase, vertexBufferSize);
				m_MeshIndexBuffer->SetData((void*)m_MeshIndexBufferBase, m_IndexCount);
			}

			if (m_IndexCount > 0)
				RenderCommand::DrawIndexed(m_MeshVertexArray, m_IndexCount);
		}

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

	struct StaticBatch {
		std::vector<uint32_t> EntitiesInBatch;

		inline void Begin() {
			for (auto buffer : m_CommonMaterialBuffers)
			{
				buffer.second.Begin();
			}
		}

		inline void Submit(uint32_t id, const std::vector<Mesh>& meshes, const glm::mat4& transform) {

			//check material
			//add to existing / create common material buffer
			for (auto mesh : meshes)
			{
				if (m_CommonMaterialBuffers.find(mesh.m_Material->GetName()) != m_CommonMaterialBuffers.end()) {
					//found buffer
					//submit vertices
					m_CommonMaterialBuffers[mesh.m_Material->GetName()].Submit(mesh, transform);

				}
				else {
					m_CommonMaterialBuffers[mesh.m_Material->GetName()] = CommonMaterialBuffer(mesh.m_Material);
					m_CommonMaterialBuffers[mesh.m_Material->GetName()].Submit(mesh, transform);
				}
			}

			EntitiesInBatch.push_back(id);
		}

		inline void End() {
			for (auto buffer : m_CommonMaterialBuffers)
			{
				buffer.second.End();
			}
		}

	private:

		std::unordered_map <std::string, CommonMaterialBuffer> m_CommonMaterialBuffers;
		
	};

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void DrawSkybox(const Scene* scene);
		static void DrawScene(const Scene* scene);
		static void EndScene();

		static void Flush();

	private:

		static void ResetAndFlush();

		static void RecreateStaticBatchBuffer();
		static void RenderStaticBatch();

		static const uint32_t MAX_TEXTURE_SLOTS = 32;
		static std::array<Texture2D*, MAX_TEXTURE_SLOTS> m_TextureSlots;

		static glm::mat4 m_View;
		static glm::mat4 m_WorldViewProjection;

		inline static VertexArray* m_MeshVertexArray = nullptr;
		inline static VertexBuffer* m_MeshVertexBuffer = nullptr;
		inline static IndexBuffer* m_MeshIndexBuffer = nullptr;

		inline static StaticBatch m_StaticBatch;
	};

}

#endif // !_ONYX_RENDERER3D_H_