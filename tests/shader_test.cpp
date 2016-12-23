#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <shader.h>
#define GL_LOG_FILE "gl.log"

bool restartGlLog() {
  FILE* file = fopen(GL_LOG_FILE, "w");
  if(!file) {
    fprintf(stderr,
      "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
      GL_LOG_FILE);
    return false;
  }
  time_t now = time(NULL);
  char* date = ctime(&now);
  fprintf(file, "GL_LOG_FILE log. local time %s", date);
  fclose(file);
  return true;
}

bool glLog(const char* message, ...) {
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    fprintf(
      stderr,
      "ERROR: could not open GL_LOG_FILE %s file for appending\n",
      GL_LOG_FILE
    );
    return false;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  fclose(file);
  return true;
}

bool glLogError(const char* message, ...) {
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    fprintf(stderr,
      "ERROR: could not open GL_LOG_FILE %s file for appending\n",
      GL_LOG_FILE);
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

const char* glTypeToString(GLenum type) {
	switch (type) {
	case GL_BOOL: return "bool";
	case GL_INT: return "int";
	case GL_FLOAT: return "float";
	case GL_FLOAT_VEC2: return "vec2";
	case GL_FLOAT_VEC3: return "vec3";
	case GL_FLOAT_VEC4: return "vec4";
	case GL_FLOAT_MAT2: return "mat2";
	case GL_FLOAT_MAT3: return "mat3";
	case GL_FLOAT_MAT4: return "mat4";
	case GL_SAMPLER_2D: return "sampler2D";
	case GL_SAMPLER_3D: return "sampler3D";
	case GL_SAMPLER_CUBE: return "samplerCube";
	case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
	default: break;
	}
	return "other";
}

void printProgrammeInfoToLog(GLuint programme) {
	int max_length = 2048;
	int actual_length = 0;
	char program_log[2048];
	glGetProgramInfoLog(programme, max_length, &actual_length, program_log);
	printf("program info log for GL index %u:\n%s", programme, program_log);
}

void describeShaderProgramme(GLuint programme) {
	printf("--------------------\nshader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf("GL_LINK_STATUS = %i\n", params);

	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf("GL_ATTACHED_SHADERS = %i\n", params);

	glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
	printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
	for (int i = 0; i < params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(
			programme,
			i,
			max_length,
			&actual_length,
			&size,
			&type,
			name
		);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(programme, long_name);
				printf("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), long_name, location);
			}
		}
		else {
			int location = glGetAttribLocation(programme, name);
			printf("  %i) type:%s name:%s location:%i\n",
				i, glTypeToString(type), name, location);
		}
	}

	glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
	printf("GL_ACTIVE_UNIFORMS = %i\n", params);
	for (int i = 0; i < params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform(
			programme,
			i,
			max_length,
			&actual_length,
			&size,
			&type,
			name
		);
		if (size > 1) {
			for (int j = 0; j < size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetUniformLocation(programme, long_name);
				printf("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), long_name, location);
			}
		}
		else {
			int location = glGetUniformLocation(programme, name);
			printf("  %i) type:%s name:%s location:%i\n",
				i, glTypeToString(type), name, location);
		}
	}

	printProgrammeInfoToLog(programme);
}

/* This is a very expensive operation, only use for debug */
bool isValid(GLuint programme) {
	glValidateProgram(programme);
	int params = -1;
	glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
	printf("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
	if (GL_TRUE != params) {
		printProgrammeInfoToLog(programme);
		return false;
	}
	return true;
}


void glfwErrorCallback(int error, const char* description) {
  glLogError("GLFW ERROR: code %i msg: %s\n", error, description);
}

int g_gl_width = 640;
int g_gl_height = 480;
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;

	/* update any perspective matrices used here */
}

void checkShaderProgrammeLinkingErrors(GLuint programme) {
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr,
			"ERROR: could not link shader programme GL index %u\n",
			programme);
		printProgrammeInfoToLog(programme);
		exit(1);
	}
}

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

int main() {
  assert(restartGlLog());

  glLog("GLFW version: %s\n", glfwGetVersionString());
  glfwSetErrorCallback(glfwErrorCallback);
  
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor* mon = glfwGetPrimaryMonitor();
  const GLFWvidmode* vmode = glfwGetVideoMode(mon);
  // For Full screen window!
  /* GLFWwindow* window = glfwCreateWindow(
	  vmode->width, vmode->height, "Triangle Test", mon, NULL
  );
  */
  GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle Test", NULL, NULL);
  glfwSetWindowSizeCallback(window, glfw_window_size_callback);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
                                  
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  float points[] = {
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
  };
  
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  SIMPLEX::Shader vertexShader("../res/shaders/test.vert", GL_VERTEX_SHADER);
  SIMPLEX::Shader fragmentShader("../res/shaders/test.frag", GL_FRAGMENT_SHADER);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fragmentShader.getShaderId());
  glAttachShader(shader_programme, vertexShader.getShaderId());
  glLinkProgram(shader_programme);
  checkShaderProgrammeLinkingErrors(shader_programme);

  char inputColourName[] = "inputColour";
  GLint inputColorLocation = glGetUniformLocation(shader_programme, inputColourName);
  glUseProgram(shader_programme);
  glUniform4f(inputColorLocation, 0.5f, 0.0f, 0.5f, 1.0f);

  while(!glfwWindowShouldClose(window)) {
	updateFpsCounter(window);
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, g_gl_width, g_gl_height);
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling 
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
  		glfwSetWindowShouldClose(window, 1);
  	}
  }


  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}