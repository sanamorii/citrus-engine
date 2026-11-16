#pragma once

#include "platform/Window.h"

namespace citrus::app {

	struct Config {
		int width = 1920;
		int height = 1080;
		const char* title = "citrus";
	};

	class Application {
	public:
		Application();
		void Run();

	private:
		void Load();
		void Update();
		void Render();
		void OnResize(int w, int h);

		platform::Window m_window;
	};
}