#include "onyxpch.h"
#include "CommonMaterialBuffer.h"
#include <Onyx/Graphics/RenderCommand.h>

#include <Onyx/Core/Application.h>

namespace Onyx {

	CommonMaterialBuffer::CommonMaterialBuffer(Material* material, const BufferLayout& bufferLayout)
	{
		m_IndexCount = 0;
		m_VertexCount = 0;
		m_Material = material;


		m_MeshVertexArray = VertexArray::Create();
		m_MeshVertexBuffer = VertexBuffer::Create();
		m_MeshVertexBuffer->SetLayout(bufferLayout);

		m_MeshVertexArray->AddVertexBuffer(m_MeshVertexBuffer);

		m_MeshIndexBuffer = IndexBuffer::Create(100000);
		m_MeshVertexArray->SetIndexBuffer(m_MeshIndexBuffer);

		if(Application::Get()->GetContext() == ApplicationContext::Runtime)
			m_MeshVertexBufferBase = new uint32_t[sizeof(Vertex3D) * 100000];
		else 
			m_MeshVertexBufferBase = new uint32_t[sizeof(EditorVertex3D) * 100000];

		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;

		m_MeshIndexBufferBase = new uint32_t[1000000];
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;
	}

	CommonMaterialBuffer::~CommonMaterialBuffer()
	{
		delete m_MeshVertexArray;
		delete m_MeshVertexBuffer;
		delete m_MeshIndexBuffer;

		delete[] m_MeshVertexBufferBase;
		delete[] m_MeshIndexBufferBase;
	}

	void CommonMaterialBuffer::Begin()
	{
		m_MeshVertexBufferWritePtr = m_MeshVertexBufferBase;
		m_MeshIndexBufferWritePtr = m_MeshIndexBufferBase;
	}

	void CommonMaterialBuffer::Submit(uint32_t id, Mesh& mesh, glm::mat4 transform)
	{
		if (Application::Get()->GetContext() == ApplicationContext::Runtime) {
			for (size_t i = 0; i < mesh.m_Vertices.size(); ++i) {

				memcpy(m_MeshVertexBufferWritePtr, &mesh.m_Vertices[i], sizeof(Vertex3D));
				((Vertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
				m_MeshVertexBufferWritePtr = (char*)m_MeshVertexBufferWritePtr + sizeof(Vertex3D);
			}

			for (size_t i = 0; i < mesh.m_Indices.size(); ++i) {

				*m_MeshIndexBufferWritePtr = mesh.m_Indices[i] + m_VertexCount;
				m_MeshIndexBufferWritePtr++;

			}
		}
		else {
			int r = (id & 0x000000FF) >> 0;
			int g = (id & 0x0000FF00) >> 8;
			int b = (id & 0x00FF0000) >> 16;

			float rF = r / 255.0F;
			float gF = g / 255.0F;
			float bF = b / 255.0F;

			for (size_t i = 0; i < mesh.m_Vertices.size(); ++i) {

				memcpy(m_MeshVertexBufferWritePtr, &mesh.m_Vertices[i], sizeof(Vertex3D));
				((EditorVertex3D*)m_MeshVertexBufferWritePtr)->Position = transform * glm::vec4(mesh.m_Vertices[i].Position, 1.0f);
				((EditorVertex3D*)m_MeshVertexBufferWritePtr)->EntityIdentifier = glm::vec4(rF, gF, bF, 1.0f);
				m_MeshVertexBufferWritePtr = (char*)m_MeshVertexBufferWritePtr + sizeof(EditorVertex3D);
			}

			for (size_t i = 0; i < mesh.m_Indices.size(); ++i) {

				*m_MeshIndexBufferWritePtr = mesh.m_Indices[i] + m_VertexCount;
				m_MeshIndexBufferWritePtr++;

			}
		}
		m_IndexCount += mesh.m_Indices.size();
		m_VertexCount += mesh.m_Vertices.size();
		++m_MeshCountInBuffer;
	}

	void CommonMaterialBuffer::End()
	{
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

}
