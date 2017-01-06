#ifndef SIMPLEX_SERVICE_LOCATOR_SERVICE_H
#define SIMPLEX_SERVICE_LOCATOR_SERVICE_H
#include <common.h>
#include <math3d.h>
#include <iServiceLocatorService.h>
#include <defaultLoggingService.h>

namespace Simplex
{
	class DefaultServiceLocatorService : public IServiceLocatorService 
	{
		public:
			ILoggingService* getLoggingService();
			void provide(ILoggingService* newLoggingService);
			void initialize();
		private:
			ILoggingService* loggingService = NULL;
	};
}
#endif