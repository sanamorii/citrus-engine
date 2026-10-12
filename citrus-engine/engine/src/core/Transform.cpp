#include "core/Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace citrus::core {
	void Transform::SetPosition(const glm::vec3& p) { m_position = p; }
	void Transform::SetScale(const glm::vec3& s) { m_scale = s; }
	void Transform::SetScale(float uniform) { Transform::SetScale(glm::vec3(uniform)); }
	void Transform::SetRotation(const glm::quat& q) { m_rotation = glm::normalize(q); }
	void Transform::SetEulerDegrees(const glm::vec3& degrees) { Transform::SetRotation(glm::quat(glm::radians(degrees))); }
}