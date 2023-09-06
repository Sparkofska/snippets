#pragma once

#include "VtProcManServiceAdapterLib_Def.h"
#include <log4cxx/logger.h>
#include <filesystem>

namespace vtprocmanserviceadapter
{
using Logger = log4cxx::LoggerPtr;

class VTPROCMANSERVICEADAPTERLIB_API Logging
{
public:
	static Logger init(const std::filesystem::path& loggerConfigFile);

	Logging(Logger logger = nullptr) : m_logger(logger) {}

	Logger getLogger() const { return m_logger; }
	void setLogger(Logger logger) const { m_logger = logger; }

	template<class T> static void logTrace(Logger l, T&& msg)                  { if (l) { LOG4CXX_TRACE(l, std::forward<T>(msg)); } }
	template<>        static void logTrace(Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_TRACE(l, msg.str()); } }

	template<class T> static void logDebug(Logger l, T&& msg)                  { if (l) { LOG4CXX_DEBUG(l, std::forward<T>(msg)); } }
	template<>        static void logDebug(Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_DEBUG(l, msg.str()); } }

	template<class T> static void logInfo (Logger l, T&& msg)                  { if (l) { LOG4CXX_INFO (l, std::forward<T>(msg)); } }
	template<>        static void logInfo (Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_INFO (l, msg.str()); } }

	template<class T> static void logWarn (Logger l, T&& msg)                  { if (l) { LOG4CXX_WARN (l, std::forward<T>(msg)); } }
	template<>        static void logWarn (Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_WARN (l, msg.str()); } }

	template<class T> static void logError(Logger l, T&& msg)                  { if (l) { LOG4CXX_ERROR(l, std::forward<T>(msg)); } }
	template<>        static void logError(Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_ERROR(l, msg.str()); } }

	template<class T> static void logFatal(Logger l, T&& msg)                  { if (l) { LOG4CXX_FATAL(l, std::forward<T>(msg)); } }
	template<>        static void logFatal(Logger l, std::ostringstream&& msg) { if (l) { LOG4CXX_FATAL(l, msg.str()); } }

	static auto ss() { return std::ostringstream{}; }

	template<class T> void logTrace(T&& msg) const { logTrace(m_logger, std::forward<T>(msg)); }
	template<class T> void logDebug(T&& msg) const { logDebug(m_logger, std::forward<T>(msg)); }
	template<class T> void logInfo (T&& msg) const { logInfo (m_logger, std::forward<T>(msg)); }
	template<class T> void logWarn (T&& msg) const { logWarn (m_logger, std::forward<T>(msg)); }
	template<class T> void logError(T&& msg) const { logError(m_logger, std::forward<T>(msg)); }
	template<class T> void logFatal(T&& msg) const { logFatal(m_logger, std::forward<T>(msg)); }

private:
	mutable Logger m_logger;
};
}
