#ifndef LOGGER_H
#define LOGGER_H
#include <prerequisites.h>
namespace Simplex
{
	class Logger 
	{
		public:
			Logger();
			bool log(const char* message...);
			bool error(const char* message...);
		private:
	};
}
#endif