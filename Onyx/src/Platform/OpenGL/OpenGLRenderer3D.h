#ifndef _ONYX_PLATFORM_OPENGL_RENDERER3D_H_
#define _ONYX_PLATFORM_OPENGL_RENDERER3D_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Graphics/Buffer.h>
#include <Onyx/Graphics/Shader.h>
#include <Onyx/Graphics/VertexArray.h>
#include <Onyx/Graphics/Renderer3D.h>
#include <Platform/OpenGL/OpenGLBuffer.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>


namespace Onyx {

	struct Vertex3D;

	class OpenGLRenderer3D : public Renderer3D {
	private:
		virtual void InitImplementation() override;
		virtual void DestroyImplementation() override;

		virtual void BeginSceneImplementation(const Camera& camera) override;
		virtual void EndSceneImplementation() override;
		virtual void FlushImplementation() override;


		virtual void DrawSceneImplementation(const Scene* scene) override;
		virtual void DrawMeshImplementation(const Mesh* mesh, const glm::vec3& position, const glm::vec3& size) override;
		virtual void DrawRotatedMeshImplementation(const Mesh* mesh, float angle, const glm::vec3& ax, const glm::vec3& position, const glm::vec3& size) override;

	private:

		static const uint32_t MAX_VERTICES = 1000000;
		static const uint32_t MAX_INDICES = 3000000;

		OpenGLVertexArray* m_MeshVertexArray;
		OpenGLVertexBuffer* m_MeshVertexBuffer;
		OpenGLIndexBuffer* m_MeshIndexBuffer;

		uint32_t m_IndexCount = 0;
		uint32_t m_VertexCount = 0;

		OpenGLShader* m_MeshBasicShader;
		OpenGLShader* m_SkyboxShader;

		//CPU mapped storage
		Vertex3D* m_MeshVertexBufferBase;
		Vertex3D* m_MeshVertexBufferWritePtr;

		uint32_t* m_MeshIndexBufferBase;
		uint32_t* m_MeshIndexBufferWritePtr;
		

		Cubemap* m_SkyboxTest;

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_