#include "Log.h"

namespace otsr
{

void Log::init(const boost::filesystem::path& loggerConfigFile)
{
	std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep to prevent bug while initializing logger
	log4cxx::xml::DOMConfigurator::configure(loggerConfigFile.string());
	std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep to prevent bug while initializing logger

	Log& log = instance();
	log.m_logger               = log4cxx::Logger::getLogger("Vitronic.PS.PsOpticalTrafficSignRecognition.log");
	log.m_classificationLogger = log4cxx::Logger::getLogger("Vitronic.PS.PsOpticalTrafficSignRecognition_ClassificationChanges.log");
	log.m_ffmpegLogger         = log4cxx::Logger::getLogger("Vitronic.PS.PsOpticalTrafficSignRecognition_ffmpeg.log");
}

log4cxx::LoggerPtr Log::logger()
{
	return instance().m_logger;
}

log4cxx::LoggerPtr Log::classificationLogger()
{
	return instance().m_classificationLogger;
}

log4cxx::LoggerPtr Log::ffmpegLogger()
{
	return instance().m_ffmpegLogger;
}

Log::~Log()
{
	// Close and flush Logger. Otherwise it will crash in destructor.
	m_logger->closeNestedAppenders();
	m_classificationLogger->closeNestedAppenders();
}

}
