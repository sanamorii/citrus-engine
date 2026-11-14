#include "gfx/Camera.h"
#include <algorithm>

namespace citrus::gfx {

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
	: m_fov(fov), m_aspect(aspect), m_near(nearPlane), m_far(farPlane){
	m_transform.SetPosition({ 0.0f,0.0f,3.0f });
	UpdateRotation();
}

void Camera::SetPosition(const glm::vec3& p) { m_transform.SetPosition(p); }
	
void Camera::Translate(const glm::vec3& p) { SetPosition(m_transform.Position() + p); }

void Camera::SetYawPitch(float yaw, float pitch) {
	m_yaw = yaw;
	m_pitch = std::clamp(pitch, -89.0f, 89.0f); // avoid flipping at poles
	UpdateRotation();
}

void Camera::Rotate(float dYaw, float dPitch) {
	SetYawPitch(m_yaw + dYaw, m_pitch + dPitch);
}

void Camera::UpdateRotation() {
	// yaw about world Y first, then pitch about the camera's local X, (no roll)
	glm::quat qYaw = glm::angleAxis(glm::radians(m_yaw), glm::vec3(0, 1, 0));
	glm::quat qPitch = glm::angleAxis(glm::radians(m_pitch), glm::vec3(1, 0, 0));
	m_transform.SetRotation(glm::normalize(qYaw * qPitch));
}

void Camera::SetAspect(float a) { m_aspect = a; }
void Camera::SetFov(float f) { m_fov = f; }

const glm::mat4& Camera::View() const {
	const glm::vec3 pos = m_transform.Position();
	m_view = glm::lookAt(pos, pos + m_transform.Forward(), m_transform.Up());
	return m_view;
}

const glm::mat4& Camera::Projection() const {
	m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	return m_projection;
}

void Camera::Apply(const Shader& shader) const {
	shader.Set("view", View());
	shader.Set("projection", Projection());
}

}