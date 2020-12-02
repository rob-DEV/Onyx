#include "onyxpch.h"
#include "StaticBatch.h"

namespace Onyx {

	StaticBatch::StaticBatch()
	{
		m_EnititiesInBatch = std::vector<uint32_t>();
		m_EnititiesInBatch.reserve(MAX_ENTITIES_IN_BATCH);
	}

	StaticBatch::~StaticBatch()
	{

	}

	void StaticBatch::Begin()
	{
		for (auto buffer : m_CommonMaterialBuffers)
		{
			buffer.second->Begin();
		}
	}

	void StaticBatch::Submit(uint32_t id, const std::vector<Mesh>& meshes, const glm::mat4& transform)
	{
		if (m_EnititiesInBatch.size() >= MAX_ENTITIES_IN_BATCH) {
			ONYX_ERROR("StaticBatch ERROR: Max Batch Size Reached!");
			return;
		}

		//check material
			//add to existing / create common material buffer
		for (auto mesh : meshes)
		{
			if (m_CommonMaterialBuffers.find(mesh.m_Material->GetName().data()) != m_CommonMaterialBuffers.end()) {
				//found buffer
				//submit vertices
				m_CommonMaterialBuffers[mesh.m_Material->GetName().data()]->Submit(id, mesh, transform);

			}
			else {
				m_CommonMaterialBuffers[mesh.m_Material->GetName().data()] = new CommonMaterialBuffer(mesh.m_Material, m_BufferLayout);
				m_CommonMaterialBuffers[mesh.m_Material->GetName().data()]->Submit(id, mesh, transform);
			}
		}

		m_EnititiesInBatch.push_back(id);
	}

	void StaticBatch::End()
	{
		for (auto buffer : m_CommonMaterialBuffers)
		{
			buffer.second->End();
		}
	}

	bool StaticBatch::IsInBatch(uint32_t id)
	{
		return std::find(m_EnititiesInBatch.begin(), m_EnititiesInBatch.end(), id) != m_EnititiesInBatch.end();
	}

}