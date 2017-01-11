#include <core.h>
#include <glRenderingService.h>

namespace Simplex
{
	Core::Core()
	{
		serviceLocatorService = new DefaultServiceLocatorService();
	}

	Core::Core(IServiceLocatorService* newServiceLocatorService)
	{
		serviceLocatorService = newServiceLocatorService;
	}

	Core::~Core()
	{
		if(serviceLocatorService) 
		{
			delete serviceLocatorService;
		}

		if(loggingService)
		{
			delete loggingService;
		}

		if(renderingService)
		{
			delete renderingService;
		}
	}

	void Core::initialize()
	{
		if(!loggingService)
		{
			setLoggingService(new DefaultLoggingService());
		}
		if(!renderingService)
		{
			setRenderingService(new GLRenderingService());
		}
		isInitialized = true;
	}

	void Core::setLoggingService(ILoggingService* newLoggingService)
	{
		if(isInitialized)
		{
			throw std::runtime_error("Cannot set service after initialization");
		}
		if(loggingService) 
		{
			delete loggingService;
		}
		loggingService = newLoggingService;
		serviceLocatorService->provide(loggingService);
	}

	void Core::setRenderingService(IRenderingService* newRenderingService)
	{
		if (isInitialized)
		{
			throw std::runtime_error("Cannot set service after initialization");
		}
		if (renderingService)
		{
			delete renderingService;
		}
		renderingService = newRenderingService;
		serviceLocatorService->provide(renderingService);
	}

	IServiceLocatorService* Core::getServiceLocatorService()
	{
		return serviceLocatorService;
	}
}