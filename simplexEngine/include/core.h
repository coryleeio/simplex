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
		    void setLoggingService(ILoggingService* loggingService);
		private:
			IServiceLocatorService* serviceLocatorService = NULL;
			ILoggingService* loggingService = NULL;
			bool isInitialized = false;
	};
}
#endif