#include <logger.h>

namespace Simplex
{
	Logger logger;

	#define LOG_FILE "log.log"
	static bool restartLog() {
	  FILE* file = fopen(LOG_FILE, "w");
	  if(!file) {
	    fprintf(stderr,
	      "ERROR: could not open LOG_FILE log file %s for writing\n",
	      LOG_FILE);
	    return false;
	  }
	  time_t now = time(NULL);
	  char* date = ctime(&now);
	  fprintf(file, "LOG_FILE log. local time %s\n", date);
	  fclose(file);
	  return true;
	}

	Logger::Logger()
	{
		log("Constructing logger...\n");
		assert(restartLog());
	}

	bool Logger::log(const char* message...)
	{
		va_list argptr;
		FILE* file = fopen(LOG_FILE, "a");
		if(!file) 
		{
			fprintf(
			  stderr,
			  "ERROR: could not open LOG_FILE %s file for appending\n",
			  LOG_FILE
			);
			return false;
		}
		va_start(argptr, message);
		vfprintf(file, message, argptr);
		va_end(argptr);
		va_start(argptr, message);
		vfprintf(stdout, message, argptr);
		va_end(argptr);

		fclose(file);
		return true;
	}

	bool Logger::error(const char* message...)
	{
		va_list argptr;
		FILE* file = fopen(LOG_FILE, "a");
		if(!file) 
		{
			fprintf(stderr,
			"ERROR: could not open LOG_FILE %s file for appending\n",
			LOG_FILE);
			return false;
		}
		va_start(argptr, message);
		vfprintf(file, message, argptr);
		va_end(argptr);
		va_start(argptr, message);
		vfprintf(stderr, message, argptr);
		va_end(argptr);
		fclose(file);
		return true;
	}
}