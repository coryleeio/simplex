#ifndef LOGGER_H
#define LOGGER_H
#include <common.h>
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