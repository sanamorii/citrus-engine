#pragma once

#include "gfx/Shader.h"
#include "core/Transform.h"

using namespace citrus::core;

namespace citrus::gfx {
	class Model {
	public:
		void Draw(); 
		void Draw(const Shader& shader);  // override a shader if we want to

	private:
		void LoadModel(const std::string& path);

		Transform m_transform;
		// std::vector<Mesh> m_meshes;  // should contain textures
	};
		
}