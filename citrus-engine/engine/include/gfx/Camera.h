#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Transform.h"
#include "gfx/Shader.h"

namespace citrus::gfx {
	class Camera {
	public:

		Camera(float fovDegrees, float aspect, float nearPlane = 1.0f, float farPlane = 1000.0f);

		// Placement
		void SetPosition(const glm::vec3& p);
		void Translate(const glm::vec3& delta);
		void SetYawPitch(float yawDeg, float pitchDeg);
		void Rotate(float dYawDeg, float pitchDeg);

		// Lens
		void SetAspect(float aspect);
		void SetFov(float fovDegrees);

		// Matrices, cache, rebuilt lazily
		const glm::mat4& View() const;
		const glm::mat4& Projection() const;
		glm::mat4 ViewProjection() const { return Projection() * View(); }

		void Apply(const Shader& shader) const;

		// Access
		const core::Transform& GetTransform() const { return m_transform; }
		const glm::vec3& Position() const { return m_transform.Position(); }
		glm::vec3 Forward() const { return m_transform.Forward(); }
		glm::vec3 Right() const { return m_transform.Right(); }
		glm::vec3 Up() const { return m_transform.Up(); }

	private:
		void UpdateRotation();

		core::Transform m_transform;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;

		float m_fov, m_aspect, m_near, m_far;

		mutable glm::mat4 m_view{ 1.0f };
		mutable glm::mat4 m_projection{ 1.0f };
	};
}