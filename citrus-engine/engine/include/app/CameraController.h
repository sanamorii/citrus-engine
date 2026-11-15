#pragma once

#include "gfx/Camera.h"

struct GLFWwindow;

namespace citrus::app {
	class CameraController {
	public:
		explicit CameraController(gfx::Camera& camera) : m_camera(camera) {}

		void Update(GLFWwindow* window, float dt);
		float moveSpeed = 5.0f;
		float sensitivity = 0.1f; // deg per px

	private:
		gfx::Camera& m_camera;
		double m_lastX = 0.0, m_lastY = 0.0;
		bool m_firstMouse = true;
	};
}