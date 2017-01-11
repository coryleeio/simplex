#ifndef SIMPLEX_CORE_H
#define SIMPLEX_CORE_H
#include <common.h>
#include <iServiceLocatorService.h>
#include <defaultServiceLocatorService.h>
#include <iLoggingService.h>
#include <defaultLoggingService.h>
namespace Simplex
{
	class Core
	{
		public:
			Core();
			Core(IServiceLocatorService* newLocator);
		    ~Core();
		    void initialize();
		    IServiceLocatorService* getServiceLocatorService();
		    void setLoggingService(ILoggingService* newLoggingService);
		    void setRenderingService(IRenderingService* newRenderingService);
		private:
			IServiceLocatorService* serviceLocatorService = NULL;
			ILoggingService* loggingService = NULL;
			IRenderingService* renderingService = NULL;
			bool isInitialized = false;
	};
}
#endif