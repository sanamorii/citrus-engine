#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace citrus::gfx {

class Shader {
public:
	Shader(const std::string name);
	~Shader();

	Shader* Link();
	Shader* Attach(const std::string& path);
	Shader* Attach(GLenum stage, const std::string& path);  // explicit


	void Bind() const;
	void Unbind() const;

	GLuint Id() const { return m_id; }
	bool IsValid() const { return m_linked && !m_failed; }

	bool IsCompute() const { return m_isCompute; }
	//void Dispatch(GLuint x, GLuint y = 1, GLuint z = 1, 
	//	GLbitfield barriers = GL_SHADER_STORAGE_BARRIER_BIT) const;

	void Set(const char* name, bool value) const;
	void Set(const char* name, int value) const;
	void Set(const char* name, unsigned int value) const;
	void Set(const char* name, float value) const;
	void Set(const char* name, const glm::vec2& v) const;
	void Set(const char* name, const glm::vec3& v) const;
	void Set(const char* name, const glm::vec4& v) const;
	void Set(const char* name, const glm::mat2& v) const;
	void Set(const char* name, const glm::mat3& v) const;
	void Set(const char* name, const glm::mat4& v) const;
private:
	GLuint		m_id = 0;
	std::string name;
	bool		m_linked = false;
	bool		m_isCompute = false;
	bool		m_failed = false;
	std::vector<GLuint> m_stages;

	static GLenum StageFromPath(const std::string& path);
	static std::string ReadFile(const std::string& path, bool& ok);
};

}
