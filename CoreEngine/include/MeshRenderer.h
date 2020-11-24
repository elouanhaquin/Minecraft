#pragma once

#include <Component.h>
#include <Model.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class MeshRenderer : public Component
	{
	private:
		Model* m_model;

	public:
		MeshRenderer();
		~MeshRenderer();

		void SetMesh(Model* p_model);
		Model* GetMesh();
	};
}