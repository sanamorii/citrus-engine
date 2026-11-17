#pragma once

#include <functional>

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

		// Frame
		bool ShouldClose() const;
		void Close();
		void SwapBuffers();
		void PollEvents();


		// Callbacks
		using ResizeCallback = std::function<void (int width, int height)>;
		void SetResizeCallback(ResizeCallback cb) { m_onResize = std::move(cb); };


		GLFWwindow* GetGLFWWindow();

	private:
		int width;
		int height;
		const char* title;
		bool Init();
		GLFWwindow* m_window;

		ResizeCallback m_onResize;
	};
}