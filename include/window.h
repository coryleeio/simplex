#ifndef WINDOW_H
#define WINDOW_H
#include <common.h>
#include <logger.h>
namespace Simplex
{
	extern Logger logger;
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