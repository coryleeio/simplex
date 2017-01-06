#include <defaultServiceLocatorService.h>

namespace Simplex
{
	ILoggingService* DefaultServiceLocatorService::getLoggingService()
	{
		return loggingService;
	}

	void DefaultServiceLocatorService::provide(ILoggingService* newLoggingService)
	{
		loggingService = newLoggingService;
	}
}