#include "app/CameraController.h"
#include <GLFW/glfw3.h>

namespace citrus::app {
	void CameraController::Update(GLFWwindow* window, float dt) {
		// mouse
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		if (m_firstMouse) {
			m_lastX = x;
			m_lastY = y;
			m_firstMouse = false;
		}
		float dx = float(x - m_lastX);
		float dy = float(y - m_lastY);
		m_lastX = x;
		m_lastY = y;

		m_camera.Rotate(-dx * sensitivity, -dy * sensitivity);

		glm::vec3 dir(0.0f);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dir += m_camera.Forward();
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dir -= m_camera.Forward();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dir += m_camera.Right();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dir -= m_camera.Right();
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) dir += glm::vec3(0, 1, 0);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) dir -= glm::vec3(0, 1, 0);

		if (glm::dot(dir, dir) > 0.0f) {
			m_camera.Translate(glm::normalize(dir) * moveSpeed * dt);
		}
		
	}
}