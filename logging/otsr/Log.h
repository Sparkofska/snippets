#pragma once

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <boost/filesystem.hpp>

#include <thread>
#include <chrono>

namespace otsr
{
class Log
{
public:
	static Log& instance()
	{
		static Log _instance;
		return _instance;
	}

	static void init(const boost::filesystem::path& loggerConfigFile);

	static log4cxx::LoggerPtr logger();
	static log4cxx::LoggerPtr classificationLogger();
	static log4cxx::LoggerPtr ffmpegLogger();

	~Log();

private:

	log4cxx::LoggerPtr m_logger;
	log4cxx::LoggerPtr m_classificationLogger;
	log4cxx::LoggerPtr m_ffmpegLogger;

	// Singleton
	Log() {}
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log& operator=(const Log&) = delete;
	Log& operator=(Log&&) = delete;
};
}
