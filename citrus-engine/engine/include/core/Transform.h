#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
	Transform() = default;

	void SetPosition(const glm::vec3& p);
	void SetScale(const glm::vec3& s);
	void SetScale(float uniform);
	void SetRotation(const glm::quat& q);
	void SetEulerDegrees(const glm::vec3& degrees);

	const glm::vec3& Position() const { return m_position; }
	const glm::vec3& Scale() const { return m_scale; }
	const glm::quat& Rotation() const { return m_rotation; }
	glm::vec3 EulerDegree() const { return glm::degrees(glm::eulerAngles(m_rotation); }

	// local axes in world space for cameras, movement, lights, etc.
	glm::vec3 Forward() const { return m_rotation * glm::vec3(0.0f, 0.0f, -1.0f); }
	glm::vec3 Right() const { return m_rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
	glm::vec3 Up() const { return m_rotation * glm::vec3(0.0f, 1.0f, 0.0f); }

	// model matrix = T * R * S
	//TODO
	const glm::mat4& Matrix() const { return NULL; }

private:
	glm::vec3 m_position{ 0.0f };
	glm::quat m_rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale{ 1.0f };

};