#include <defaultServiceLocatorService.h>

namespace Simplex
{
	void DefaultServiceLocatorService::provide(ILoggingService* newLoggingService)
	{
		loggingService = newLoggingService;
	}

	void DefaultServiceLocatorService::provide(IRenderingService* newRenderingService)
	{
		renderingService = newRenderingService;
	}

	ILoggingService* DefaultServiceLocatorService::getLoggingService()
	{
		return loggingService;
	}

	IRenderingService* DefaultServiceLocatorService::getRenderingService()
	{
		return renderingService;
	}
}