#include "platform/Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

citrus::platform::Window::Window(const char* title, int width, int height) {
	this->height = height;
	this->width = width;
	this->title = title;

	if (!Init()) {
		glfwTerminate();
	}
}

citrus::platform::Window::~Window() {
	glfwTerminate();
}

bool citrus::platform::Window::Init() {
	if (!glfwInit()) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	m_window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
	if (m_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	// TODO: center window

	glfwMakeContextCurrent(m_window);
	return true;
}

void citrus::platform::Window::Update() {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

int citrus::platform::Window::GetWindowWidth() { return width; }
int citrus::platform::Window::GetWindowHeight() { return height; }
GLFWwindow* citrus::platform::Window::GetGLFWWindow() { return m_window; }

bool citrus::platform::Window::SetWindowResolution(int opt) {
	return false; // TODO: ...
}
bool citrus::platform::Window::ShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void citrus::platform::Window::Close() {
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void citrus::platform::Window::SwapBuffers() {
	glfwSwapBuffers(m_window);
}

void citrus::platform::Window::PollEvents() {
	glfwPollEvents();
}

void citrus::platform::Window::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}