#include "core/Cube.h"


namespace citrus::core {

	Cube::Cube() : m_tex("assets/textures/container.jpg") {
		Load();
	}

	Cube::~Cube() {
		Release();
	}

	void Cube::Load() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// bind buffer
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		// define buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//	normals attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		//	colour attribute
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture attribute
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//  unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Texture
		m_tex.ApplyParameters();
		m_tex.LoadTexture();
	}

	void Cube::Release() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Cube::Draw(gfx::Shader& shad) {
		
		glm::mat4 model = m_transform.Matrix();
		shad.Set("model", model);
		
		glBindTexture(GL_TEXTURE_2D, m_tex.ID());

		glBindVertexArray(VAO);  // bind vao
		glDrawArrays(GL_TRIANGLES, 0, sizeof(this->vertices) / sizeof(float) / 8);
		glBindVertexArray(0);  // unbind
	}

	core::Transform& Cube::GetTransform() {
		return m_transform;
	}

}