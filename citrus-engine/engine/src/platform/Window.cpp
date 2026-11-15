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

	window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	// TODO: center window

	glfwMakeContextCurrent(window);
	return true;
}

void citrus::platform::Window::Update() {
	glfwPollEvents();
	glfwSwapBuffers(window);
}