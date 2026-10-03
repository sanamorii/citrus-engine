#include "core/Application.h"

namespace Citrus {
	struct Config {
		int				width = 1920;
		int				height = 1080;
		const char*		window_title = "citrus";
	};

	class Application {
	public:
		bool init(const Config& config) {
			m_config = config;
		}

	private:
		Config m_config;
	};
}