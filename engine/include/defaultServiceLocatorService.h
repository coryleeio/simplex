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
			void provide(ILoggingService* newLoggingService);
			void provide(IRenderingService* newRenderingService);
			ILoggingService* getLoggingService();
			IRenderingService* getRenderingService();
		private:
			ILoggingService* loggingService = NULL;
			IRenderingService* renderingService = NULL;
	};
}
#endif