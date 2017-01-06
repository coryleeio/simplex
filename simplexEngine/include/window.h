#ifndef SIMPLEX_WINDOW_H
#define SIMPLEX_WINDOW_H
#include <common.h>
#include <iLoggingService.h>
namespace Simplex
{
	class Window
	{
		public:
			Window();
			bool shouldClose();
			void close();
			void draw();
			void clear(); 
		private:
			GLuint windowId;
			GLFWwindow* window;
	};
}

#endif