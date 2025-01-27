#include "log.h"

#include <iostream>
#include <ostream>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace GRC {

	std::shared_ptr<spdlog::logger> Log::logger;

	void Log::init() {
		spdlog::set_pattern("%^[%l]: %v%$");
		logger = spdlog::stdout_color_mt("grc");
		logger->set_level(spdlog::level::trace);
	}

}