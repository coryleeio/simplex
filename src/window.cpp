#include <window.h>

namespace Simplex
{
	extern Logger logger;

	static void handleError(int error, const char* description) {
	  printf("GLFW ERROR: code %i msg: %s\n", error, description);
	}

	static void handleResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		/* update any perspective matrices used here */
	}

	static void updateFpsCounter(GLFWwindow* window) {
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

	Window::Window() 
	{
		logger.log("Creating window...\n");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		printf("GLFW version: %s\n", glfwGetVersionString());
		glfwSetErrorCallback(handleError);

		if (!glfwInit()) {
		  fprintf(stderr, "ERROR: could not start GLFW3\n");
		  throw std::exception();
		} 

		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);

		  // For Full screen window!
		  /* GLFWwindow* window = glfwCreateWindow(
			  vmode->width, vmode->height, "Triangle Test", mon, NULL
		  );
		  */

		window = glfwCreateWindow(640, 480, "Triangle Test", NULL, NULL);
		glfwSetWindowSizeCallback(window, handleResize);
		if (!window) {
		  fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		  glfwTerminate();
		  throw std::exception();
		}

		glfwMakeContextCurrent(window);

		// start GLEW extension handler
		glewExperimental = GL_TRUE;
		glewInit();
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	}

	void Window::draw()
	{
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		    close();
		}
	}

	void Window::clear() 
	{
		updateFpsCounter(window);
	    // wipe the drawing surface clear
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(window, 1);
	}

	bool Window::shouldClose() 
	{
		return glfwWindowShouldClose(window);
	}
}