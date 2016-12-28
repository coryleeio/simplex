#include <programme.h>

namespace Simplex
{
	extern Logger logger;
	
	static const char* glTypeToString(GLenum type) {
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

	static void printProgrammeInfoToLog(GLuint programme) {
		int max_length = 2048;
		int actual_length = 0;
		char program_log[2048];
		glGetProgramInfoLog(programme, max_length, &actual_length, program_log);
		logger.error("program info log for GL index %u:\n%s", programme, program_log);
	}

	static void checkShaderProgrammeLinkingErrors(GLuint programme) {
		int params = -1;
		glGetProgramiv(programme, GL_LINK_STATUS, &params);
		if (GL_TRUE != params) {
			fprintf(stderr,
				"ERROR: could not link shader programme GL index %u\n",
				programme);
			printProgrammeInfoToLog(programme);
			throw std::exception();
		}
	}

	static void describeShaderProgramme(GLuint programme) {
		logger.log("--------------------\nshader programme %i info:\n", programme);
		int params = -1;
		glGetProgramiv(programme, GL_LINK_STATUS, &params);
		logger.log("GL_LINK_STATUS = %i\n", params);

		glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
		logger.log("GL_ATTACHED_SHADERS = %i\n", params);

		glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
		logger.log("GL_ACTIVE_ATTRIBUTES = %i\n", params);
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
					logger.log("  %i) type:%s name:%s location:%i\n",
						i, glTypeToString(type), long_name, location);
				}
			}
			else {
				int location = glGetAttribLocation(programme, name);
				logger.log("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), name, location);
			}
		}

		glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
		logger.log("GL_ACTIVE_UNIFORMS = %i\n", params);
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
					logger.log("  %i) type:%s name:%s location:%i\n",
						i, glTypeToString(type), long_name, location);
				}
			}
			else {
				int location = glGetUniformLocation(programme, name);
				logger.log("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), name, location);
			}
		}

		printProgrammeInfoToLog(programme);
	}

	/* This is a very expensive operation, only use for debug */
	static bool isValid(GLuint programme) {
		glValidateProgram(programme);
		int params = -1;
		glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
		logger.log("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
		if (GL_TRUE != params) {
			printProgrammeInfoToLog(programme);
			return false;
		}
		return true;
	}

	Programme::Programme(Shader& vertexShader, Shader& fragmentShader)
	{
		logger.log("Building shader programme...\n");
		vertexShaderId = vertexShader.getShaderId();
		fragmentShaderId = fragmentShader.getShaderId();
		programmeId = glCreateProgram();
		glAttachShader(programmeId, fragmentShader.getShaderId());
		glAttachShader(programmeId, vertexShader.getShaderId());
		glLinkProgram(programmeId);
		checkShaderProgrammeLinkingErrors(programmeId);
		isValid(programmeId);
	}

	GLuint Programme::getVertexShaderId()
	{
		return vertexShaderId;
	}

	GLuint Programme::getFragmentShaderId()
	{
		return fragmentShaderId;
	}

	GLuint Programme::getProgrammeId() 
	{
		return programmeId;
	}

	void Programme::activate()
	{
		glUseProgram(programmeId);
	}

	void Programme::setVector4f(const char* inputName, float x,float y,float z,float w)
	{
		GLint inputLocation = glGetUniformLocation(programmeId, inputName);
		glUniform4f(inputLocation, x, y, z, w);
	}

	void Programme::setFloat(const char* inputName, float input)
	{
		GLint inputLocation = glGetUniformLocation(programmeId, inputName);
		assert(inputLocation != 0xFFFFFFFF);
		glUniform1f(inputLocation, input);
	}
}