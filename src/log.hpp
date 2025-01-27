#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace GRC {

	class Log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger> &get_logger() { return logger; }
	private:
		static std::shared_ptr<spdlog::logger> logger;
	};

}

#define LOG_TRACE(...)	      ::GRC::Log::get_logger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	      ::GRC::Log::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)	      ::GRC::Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	      ::GRC::Log::get_logger()->error(__VA_ARGS__)
#define LOG_FATAL(...)	      ::GRC::Log::get_logger()->fatal(__VA_ARGS__)