#include "app/Application.h"

#include <GLFW/glfw3.h>

citrus::app::Application::Application() 
	: m_window({ "citrus", 800, 600 }) {
	m_window.SetResizeCallback([this](int w, int h) { OnResize(w, h); });
	Load();
}

void citrus::app::Application::Load() {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_FRAMEBUFFER_SRGB);
}

void citrus::app::Application::Run() {

	while (!m_window.ShouldClose()) {
		// ...

		Update();
		Render();

		m_window.SwapBuffers();
		m_window.PollEvents();
	}
}



void citrus::app::Application::Update() {
	// object updates go here
}

void citrus::app::Application::Render() {
	// Render logic goes here
}



void citrus::app::Application::OnResize(int w, int h) {
	glViewport(0, 0, w, h);
}
