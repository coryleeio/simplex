#include <core.h>

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
	}

	void Core::initialize()
	{
		if(!loggingService)
		{
			setLoggingService(new DefaultLoggingService());
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
	}

	IServiceLocatorService* Core::getServiceLocatorService()
	{
		return serviceLocatorService;
	}
}