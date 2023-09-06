#include "Log.h"
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>
#include <thread>

using namespace vtprocmanserviceadapter;

// Helper to ensure recursive close() of nested appenders
class LoggerRAIIWrapper
{
public:
	LoggerRAIIWrapper(log4cxx::LoggerPtr l) : m_logger(l) { }
	virtual ~LoggerRAIIWrapper() { if (m_logger) m_logger->closeNestedAppenders(); }

private:
	log4cxx::LoggerPtr m_logger;
};

Logger Logging::init(const std::filesystem::path& loggerConfigFile)
{
	if (loggerConfigFile.extension() == ".xml")
		log4cxx::xml::DOMConfigurator::configureAndWatch(loggerConfigFile.string());
	else
		log4cxx::PropertyConfigurator::configureAndWatch(loggerConfigFile.string());

	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep to prevent bug while initializing async logger

	auto logger = log4cxx::Logger::getLogger("VtProcManServiceAdapterLogger");

	static LoggerRAIIWrapper l(logger);

	return logger;
}
