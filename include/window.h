#ifndef WINDOW_H
#define WINDOW_H
#include <common.h>

namespace Simplex
{
	class Window
	{
		public:
			Window();
			GLFWwindow* getWindow();
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