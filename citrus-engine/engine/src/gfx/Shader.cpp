#include "gfx/Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace citrus::gfx {

GLenum Shader::StageFromPath(const std::string& path) {
	const std::string ext = std::filesystem::path(path).extension().string();
	if (ext == ".vert") return GL_VERTEX_SHADER;
	if (ext == ".frag") return GL_FRAGMENT_SHADER;
	if (ext == ".geom") return GL_GEOMETRY_SHADER;
	if (ext == ".tesc") return GL_TESS_CONTROL_SHADER;
	if (ext == ".tese") return GL_TESS_EVALUATION_SHADER;
	if (ext == ".comp") return GL_COMPUTE_SHADER;
	return 0;
}

std::string Shader::ReadFile(const std::string& path, bool& ok) {
	std::ifstream file(path);
	if (!file) {
		ok = false;
		return {};
	}
	std::stringstream ss;
	ss << file.rdbuf();
	ok = true;
	return ss.str();
}


Shader* Shader::Attach(const std::string& path) {
	bool ok = false;
	const std::string shader_source = ReadFile(path, ok);
	const char* src = shader_source.c_str();
	GLenum stage = Shader::StageFromPath(path);

	if (stage == 0) {
		std::cerr << "[Shader] Unknown shader extension: " << path << "\n";
		m_failed = true;
		return this;
	}

	unsigned int shader = glCreateShader(stage);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);	

	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[1024];
		glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
		std::cerr << "[Shader] Compile error in " << path << ":\n" << log << "\n";
		glDeleteShader(shader);
		m_failed = true;
		return this;
	}

	m_stages.push_back(shader);
	return this;
}

Shader* Shader::Attach(GLenum stage, const std::string& path) {
	// TODO

	return this;
}

Shader* Shader::Link() {
	if (m_failed || m_stages.empty()) {
		if (!m_failed)
			std::cerr << "[Shader] Shader::Link() called with no shaders attached\n";
		m_failed = true;
		for (GLuint s : m_stages) glDeleteShader(s);
		m_stages.clear();
		return this;
	}

	m_id = glCreateProgram();
	for (GLuint s : m_stages) glAttachShader(m_id, s);
	glLinkProgram(m_id);

	GLuint success = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) {
		char log[1024];
		glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
		std::cerr << "[Shader] Link error:\n" << log << "\n";
		m_failed;
	}
	else {
		m_linked = true;
	}

	for (GLuint s : m_stages) {
		glDetachShader(m_id, s);
		glDeleteShader(s)
	}

	m_stages.clear();
	return this;
}

void Shader::Bind() const {
	if (IsValid()) glUseProgram(m_id);
}

void Shader::Unbind() const {
	if (IsValid()) glUseProgram(0);
}

void Shader::Set(const char* name, bool value) const {
	glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::Set(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::Set(const char* name, unsigned int value) const {
	glUniform1ui(glGetUniformLocation(m_id, name), value);
}

void Shader::Set(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::Set(const char* name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}
void Shader::Set(const char* name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}

void Shader::Set(const char* name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}

void Shader::Set(const char* name, const glm::mat2& value) const {
	glUniformMatrix2fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::Set(const char* name, const glm::mat3& value) const {
	glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::Set(const char* name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
}

}
