#pragma once

struct GLFWwindow;

namespace citrus::platform {
	class Window {
	public:
		Window(const char* title, int width, int height);
		~Window();

		void Update();

		int GetWindowWidth();
		int GetWindowHeight();

		bool SetWindowResolution(int opt);

		GLFWwindow* GetGLFWWindow();

	private:
		int width;
		int height;
		const char* title;
		bool Init();
		GLFWwindow* window;
	}
}