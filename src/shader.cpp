#include <shader.h>

namespace Simplex
{
	static std::string getFileContents(const char *filename) 
	{
		std::string shaderString;
		std::string line;
		std::ifstream stream(filename);
		if (!stream)
		{
			fprintf(stderr, "Failed to find shader: '%s'\n", filename);
			exit(1);
		}

		while (std::getline(stream, line))
		{
			shaderString += line;
			// Add newline if not at end of file
			if (stream.peek() != EOF) shaderString += '\n';
		}
		return shaderString;
	}

	static void printShaderInfoLog(GLuint shader_index) 
	{
		int max_length = 2048;
		int actual_length = 0;
		char shader_log[2048];
		glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
		printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
	}

	static void checkShaderCompileErrors(GLuint shader_index) 
	{
		int params = -1;
		glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader_index);
			printShaderInfoLog(shader_index);
			exit(1);
		}
	}

	Shader::Shader(const char *filename, GLenum shaderType) 
	{
		std::string shader_str = getFileContents(filename);
		const char* shader_content = shader_str.c_str();
		shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, &shader_content, NULL);
		glCompileShader(shaderId);
		checkShaderCompileErrors(shaderId);
	}

	GLuint Shader::getShaderId() 
	{
		return shaderId;
	}
}