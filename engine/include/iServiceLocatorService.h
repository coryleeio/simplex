#ifndef SIMPLEX_INTERFACE_SERVICE_LOCATOR_SERVICE_H
#define SIMPLEX_INTERFACE_SERVICE_LOCATOR_SERVICE_H
#include <common.h>
#include <ILoggingService.h>
#include <iRenderingService.h>
namespace Simplex
{
	class IServiceLocatorService 
	{
		public:
			virtual void provide(ILoggingService* newLoggingService) = 0;
			virtual void provide(IRenderingService* newRenderingService) = 0;
			virtual ILoggingService* getLoggingService() = 0;
			virtual IRenderingService* getRenderingService() = 0;
	};
}
#endif