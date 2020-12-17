#ifndef _ONYX_EDITOR_GIZMO_H_
#define _ONYX_EDITOR_GIZMO_H_

#include <Onyx/Core/Core.h>
#include <Onyx/Core/TimeStep.h>

#include <Onyx/Camera/Camera.h>
#include <Onyx/Graphics/Model.h>
#include <Onyx/Entity/Components.h>
#include <Onyx/Graphics/Framebuffer.h>
#include <Onyx/Graphics/VertexArray.h>


namespace Onyx {

	enum class GizmoState {
		TRANSFORM,
		ROTATE,
		SCALE
	};

	enum class AXIS {
		NONE,
		X,
		Y,
		Z
	};

	struct GizmoData {
		GizmoState State;
		glm::mat4 GizmoTransformMatrix = glm::mat4(1.0f);

		AXIS Axis = AXIS::NONE;


	};

	struct GizmoModelData {

		Model* Transform;
		Model* Rotate;
		Model* Scale;

		Model* Active;

	};

	struct RenderData {
		Framebuffer* Framebuffer;
		glm::mat4 ViewProjectionMatrix;

		VertexArray* GizmoVAO = nullptr;
		VertexBuffer* GizmoVBO = nullptr;
		IndexBuffer* GizmoIBO = nullptr;

		void* MeshVertexBufferBase = nullptr;
		void* MeshVertexBufferWritePtr = nullptr;

		uint32_t* MeshIndexBufferBase = nullptr;
		uint32_t* MeshIndexBufferWritePtr = nullptr;

		uint32_t IndexCount = 0;
		uint32_t VertexCount = 0;

		//Gizmo selection buffers
		uint32_t SelectionPixelBuffers[2];
		uint32_t PboIndex = 0;
		uint32_t PboNextIndex = 0;

	};

	struct GizmoVertex {
		glm::vec3 Position;
		glm::vec4 Color;
	};


	struct RGBA
	{
		uint8_t R = 0;
		uint8_t G = 0;
		uint8_t B = 0;
		uint8_t A = 0;
	};

	class ONYX_API Gizmo {
	public:

		static void Init();
		static void SetState(GizmoState state);
		static GizmoState GetState();
		static void Manipulate(Timestep ts, const Camera& camera, glm::mat4& modelTransform);

		static Framebuffer* GetFramebuffer() { return s_RendererData.Framebuffer; }

	private:
		static GizmoData s_GizmoData;
		static GizmoModelData s_GizmoModelData;
		static RenderData s_RendererData;

		static void Render();
		inline static bool s_Initialized = false;

		glm::mat4 transform;

	};

}

#endif