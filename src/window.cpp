#include <window.h>

namespace SIMPLEX
{
	void updateFpsCounter(GLFWwindow* window) {
		static double previous_seconds = glfwGetTime();
		static int frame_count;
		double current_seconds = glfwGetTime();
		double elapsed_seconds = current_seconds - previous_seconds;
		if (elapsed_seconds > 0.25) {
			previous_seconds = current_seconds;
			double fps = (double)frame_count / elapsed_seconds;
			char tmp[128];
			sprintf(tmp, "opengl @ fps: %.2f", fps);
			glfwSetWindowTitle(window, tmp);
			frame_count = 0;
		}
		frame_count++;
	}

	Window::Window(const char *title,int width, int height) {
		  if (!window) {
		    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		    glfwTerminate();
		    return 1;
		  }

		  /* GLFWwindow* window = glfwCreateWindow(
		   vmode->width, vmode->height, title, mon, NULL
		  );
		  */
		  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
		  glfwSetWindowSizeCallback(window, handleResize);
		  glfwMakeContextCurrent(window);
	}

	Window::drawFrame() {
		updateFpsCounter(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		  glfwSetWindowShouldClose(window, 1);
		}
	}

	Window::handleResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}