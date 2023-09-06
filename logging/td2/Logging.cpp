#include "Logging.h"

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

#include <chrono>
#include <thread>

using namespace td2;

Log Log::m_instance;

log4cxx::LoggerPtr Log::m_loggerTD2Info = log4cxx::Logger::getLogger("Vitronic.PS.pstdprocessor.serialmonitor.TD2_info");

void Log::Init(const char *cfgFile)
{
	std::string loggingConfigFilename = cfgFile;
	std::cout << "Initializing logger from " << loggingConfigFilename << " (and sleep for 2sec)." << std::endl;
	//std::string loggingConfigFilename = "D:/PsTD2/config/pstd2processor/pstdprocessor.logging.develop.xml";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	log4cxx::xml::DOMConfigurator::configure(loggingConfigFilename);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Log::m_loggerTD2Info = log4cxx::Logger::getLogger("Vitronic.PS.pstdprocessor.serialmonitor.TD2_info");
}

void Log::cleanUp()
{
	Log::m_loggerTD2Info->closeNestedAppenders();
	Log::m_loggerTD2Info->removeAllAppenders();
	//log4cxx::xml::DOMConfigurator::releaseRef();
}
