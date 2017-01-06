#ifndef SIMPLEX_INTERFACE_SERVICE_LOCATOR_SERVICE_H
#define SIMPLEX_INTERFACE_SERVICE_LOCATOR_SERVICE_H
#include <common.h>
#include <ILoggingService.h>
namespace Simplex
{
	class IServiceLocatorService 
	{
		public:
			virtual ILoggingService* getLoggingService() = 0;
			virtual void provide(ILoggingService* newLoggingService) = 0;
	};
}
#endif