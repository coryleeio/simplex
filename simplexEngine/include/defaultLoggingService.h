#ifndef SIMPLEX_DEFAULT_LOGGING_SERVICE_H
#define SIMPLEX_DEFAULT_LOGGING_SERVICE_H
#include <common.h>
#include <iLoggingService.h>
namespace Simplex
{
	class DefaultLoggingService : public ILoggingService 
	{
		public:
			DefaultLoggingService();
			~DefaultLoggingService();
			bool log(const char* message...);
			bool error(const char* message...);
		private:
	};
}
#endif