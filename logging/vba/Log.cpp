#include "Log.hpp"

#pragma warning(push, 0)
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#pragma warning(pop)

namespace VariableSpeedLimitSign
{
std::shared_ptr<VariableSpeedLimitSign::Log4cxxLogWrapper> Log4cxxLogWrapper::initFromFile(const boost::filesystem::path& configFile)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(1)); // sleep to prevent bug while initializing logger
	log4cxx::xml::DOMConfigurator::configure(configFile.string());
	boost::this_thread::sleep_for(boost::chrono::seconds(1)); // sleep to prevent bug while initializing logger

	return std::shared_ptr<Log4cxxLogWrapper>(new Log4cxxLogWrapper(
		log4cxx::Logger::getLogger("vitronic.poliscan.PsVariableSpeedLimitSign")));
}

Log4cxxLogWrapper::Log4cxxLogWrapper(log4cxx::LoggerPtr logger)
	: LogWrapper()
	, m_logger(logger)
{ }

Log4cxxLogWrapper::~Log4cxxLogWrapper()
{
	// Close and flush Logger. Otherwise it will crash in destructor.
	m_logger->closeNestedAppenders();
}

void Log4cxxLogWrapper::trace(const std::string& msg)
{
	if (m_logger)
		LOG4CXX_TRACE(m_logger, msg);
}

void Log4cxxLogWrapper::debug(const std::string& msg)
{
	if (m_logger)
		LOG4CXX_DEBUG(m_logger, msg);
}

void Log4cxxLogWrapper::info(const std::string& msg)
{
	if (m_logger)
		LOG4CXX_INFO(m_logger, msg);
}

void Log4cxxLogWrapper::warn(const std::string& msg)
{
	if (m_logger)
		LOG4CXX_WARN(m_logger, msg);
}

void Log4cxxLogWrapper::error(const std::string& msg)
{
	if (m_logger)
		LOG4CXX_ERROR(m_logger, msg);
}

log4cxx::LoggerPtr Log4cxxLogWrapper::logger() const
{
	return m_logger;
}

void Log::init(const boost::filesystem::path& loggerConfigFile)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(1)); // sleep to prevent bug while initializing logger
	log4cxx::xml::DOMConfigurator::configure(loggerConfigFile.string());
	boost::this_thread::sleep_for(boost::chrono::seconds(1)); // sleep to prevent bug while initializing logger

	Log& log = instance();
	log.m_logger = log4cxx::Logger::getLogger("vitronic.poliscan.PsVariableSpeedLimitSign");
}

log4cxx::LoggerPtr Log::logger()
{
	return instance().m_logger;
}

Log::~Log()
{
	// Close and flush Logger. Otherwise it will crash in destructor.
	if(m_logger)
		m_logger->closeNestedAppenders();
}

}
