#ifndef SIMPLEX_INTERFACE_LOGGING_SERVICE_H
#define SIMPLEX_INTERFACE_LOGGING_SERVICE_H
namespace Simplex
{
	class ILoggingService 
	{
		public:
			virtual bool log(const char* message...) = 0;
			virtual bool error(const char* message...) = 0;
	};
}
#endif