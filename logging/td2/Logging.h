#pragma once

#include <string>
#include <sstream>

#include "log4cxx/logger.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include "TLException.h"
#include "opencv2/core.hpp"

#ifdef _DEBUG
#define WATCH(x) std::cout << (#x) << ": " << (x) << std::endl;
#define PRINTD(x) std::cout << x << std::endl;
#else
#define WATCH(x)
#define PRINTD(x)
#endif

/*
* helper macro for simple access to stringstreams
*/
#define STMSTR(STREAMMSG) [&]()->std::string{std::stringstream oStrStr_4AE80E30_FBCE_4FCC_A15C_D9F26679E350; oStrStr_4AE80E30_FBCE_4FCC_A15C_D9F26679E350 << STREAMMSG; return oStrStr_4AE80E30_FBCE_4FCC_A15C_D9F26679E350.str();}()

namespace td2 {

class Log
{
public:
	static log4cxx::LoggerPtr m_loggerTD2Info;

	static void Init(const char *cfgFile);

	static void cleanUp();

	static void trace(const std::string& msg) { LOG4CXX_TRACE(Log::m_loggerTD2Info, msg); }
	static void debug(const std::string& msg) { LOG4CXX_DEBUG(Log::m_loggerTD2Info, msg); }
	static void info(const std::string& msg) { LOG4CXX_INFO(Log::m_loggerTD2Info, msg); }
	static void warn(const std::string& msg) { LOG4CXX_WARN(Log::m_loggerTD2Info, msg); }
	static void error(const std::string& msg) { LOG4CXX_ERROR(Log::m_loggerTD2Info, msg); }
	static void fatal(const std::string& msg) { LOG4CXX_FATAL(Log::m_loggerTD2Info, msg); }

	static void trace(const std::string& msg1, const std::string& msg2) { LOG4CXX_TRACE(Log::m_loggerTD2Info, msg1 << "::" << msg2); }
	static void debug(const std::string& msg1, const std::string& msg2) { LOG4CXX_DEBUG(Log::m_loggerTD2Info, msg1 << "::" << msg2); }
	static void info (const std::string& msg1, const std::string& msg2) { LOG4CXX_INFO (Log::m_loggerTD2Info, msg1 << "::" << msg2); }
	static void warn (const std::string& msg1, const std::string& msg2) { LOG4CXX_WARN (Log::m_loggerTD2Info, msg1 << "::" << msg2); }
	static void error(const std::string& msg1, const std::string& msg2) { LOG4CXX_ERROR(Log::m_loggerTD2Info, msg1 << "::" << msg2); }
	static void fatal(const std::string& msg1, const std::string& msg2) { LOG4CXX_FATAL(Log::m_loggerTD2Info, msg1 << "::" << msg2); }

	static void monitorIncomingRequest(const std::string& string)
	{
		LOG4CXX_INFO(Log::m_loggerTD2Info, string);
		LOG4CXX_INFO(Log::m_loggerTD2, string);
	} 

	static void monitorExceptionCaught(const std::string& errorMsg, const std::string& className="", const std::string& functionName="", const bool writeToCerr=true)
	{
		std::string locInfo = "Exception caught";
		if (!className.empty())
			locInfo += " in " + className;
		if (!functionName.empty())
			locInfo += "::" + functionName;

		if (writeToCerr)
			std::cerr << locInfo << " " << errorMsg << std::endl;

		LOG4CXX_ERROR(Log::m_loggerTD2Info, locInfo << " " << errorMsg);
	}
	static void monitorExceptionCaught(const std::exception& error, const std::string& className="", const std::string& functionName="", const bool writeToCout=true)
	{
		monitorExceptionCaught("std::exception: " + std::string(error.what()), className, functionName, writeToCout);
	}
	static void monitorExceptionCaught(const cv::Exception& error, const std::string& className="", const std::string& functionName="", const bool writeToCout=true)
	{
		monitorExceptionCaught("cv::Exception: " + std::string(error.what()), className, functionName, writeToCout);
	}
	static void monitorExceptionCaught(const TLException& error, const std::string& className="", const std::string& functionName="", const bool writeToCout=true)
	{
		monitorExceptionCaught("TLException: " + std::string(error.what()), className, functionName, writeToCout);
	}
	
private:
	Log() = default;
	virtual ~Log() = default;

	static Log m_instance;
};

}