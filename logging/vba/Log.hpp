#ifndef __Log_HPP__
#define __Log_HPP__

#pragma warning(push, 0)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_guard.hpp>
#include <log4cxx/asyncappender.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/logger.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/xml/domconfigurator.h>
#pragma warning(pop)

namespace VariableSpeedLimitSign
{
class LogWrapper
{
public:
	LogWrapper() {}
	virtual ~LogWrapper() {}

	virtual void trace(const std::string& msg) = 0;
	virtual void debug(const std::string& msg) = 0;
	virtual void info(const std::string& msg) = 0;
	virtual void warn(const std::string& msg) = 0;
	virtual void error(const std::string& msg) = 0;
};

class Log4cxxLogWrapper : public LogWrapper
{
public:

	static std::shared_ptr<Log4cxxLogWrapper> initFromFile(const boost::filesystem::path& configFile);

	Log4cxxLogWrapper(log4cxx::LoggerPtr logger);

	virtual ~Log4cxxLogWrapper();

	void trace(const std::string& msg) override;
	void debug(const std::string& msg) override;
	void info(const std::string& msg) override;
	void warn(const std::string& msg) override;
	void error(const std::string& msg) override;

	log4cxx::LoggerPtr logger() const;

private:
	log4cxx::LoggerPtr m_logger;
};

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

	~Log();

private:

	log4cxx::LoggerPtr m_logger;

	// Singleton
	Log() {}
	Log(const Log&) { throw "Don't call ctor of Singleton!"; }
	Log(Log&&)      { throw "Don't call ctor of Singleton!"; }
	Log& operator=(const Log&) { throw "Don't copy Singleton!"; }
	Log& operator=(Log&&)      { throw "Don't copy Singleton!"; }
};
}

#endif
