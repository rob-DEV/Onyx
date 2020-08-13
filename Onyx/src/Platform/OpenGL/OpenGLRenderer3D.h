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
		virtual void InitImplementation();
		virtual void DestroyImplementation();

		virtual void BeginSceneImplementation(const OrthographicCamera& camera);
		virtual void EndSceneImplementation();
		virtual void FlushImplementation();


		virtual void DrawCubeImplementation(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
		

	private:


		static const uint32_t MAX_CUBES = 100;
		static const uint32_t MAX_CUBE_VERTICES = MAX_CUBES * 8;
		static const uint32_t MAX_CUBE_INDICES = MAX_CUBES * 36;


		static const float cube_vertices[];
		static const uint32_t cube_elements[];

		//CONSTANT
		glm::vec4 m_CubePositions[8];

		OpenGLVertexArray* m_MeshVertexArray;
		OpenGLVertexBuffer* m_MeshVertexBuffer;
		OpenGLIndexBuffer* m_MeshIndexBuffer;

		uint32_t m_IndexCount = 0;
		uint32_t m_VertexCount = 0;

		OpenGLShader* m_MeshBasicShader;

		//CPU mapped storage
		Vertex3D* m_MeshVertexBufferData;
		Vertex3D* m_MeshVertexBufferWritePtr;
		

	};

}

#endif // !_ONYX_GRAPHICS_RENDERER2D_H_