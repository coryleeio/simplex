#include <program.h>

namespace Simplex
{
	extern Logger logger;
	
	static const char* glTypeToString(GLenum type) 
	{
		switch (type) 
		{
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

	static void printProgramInfoToLog(GLuint program) 
	{
		int max_length = 2048;
		int actual_length = 0;
		char program_log[2048];
		glGetProgramInfoLog(program, max_length, &actual_length, program_log);
		logger.error("program info log for GL index %u:\n%s", program, program_log);
	}

	static void checkShaderProgramLinkingErrors(GLuint program) 
	{
		int params = -1;
		glGetProgramiv(program, GL_LINK_STATUS, &params);
		if (GL_TRUE != params) 
		{
			fprintf(stderr,
				"ERROR: could not link shader program GL index %u\n",
				program);
			printProgramInfoToLog(program);
			throw std::exception();
		}
	}

	static void describeShaderProgram(GLuint program) 
	{
		logger.log("--------------------\nshader program %i info:\n", program);
		int params = -1;
		glGetProgramiv(program, GL_LINK_STATUS, &params);
		logger.log("GL_LINK_STATUS = %i\n", params);

		glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
		logger.log("GL_ATTACHED_SHADERS = %i\n", params);

		glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
		logger.log("GL_ACTIVE_ATTRIBUTES = %i\n", params);
		for (int i = 0; i < params; i++) 
		{
			char name[64];
			int max_length = 64;
			int actual_length = 0;
			int size = 0;
			GLenum type;
			glGetActiveAttrib(
				program,
				i,
				max_length,
				&actual_length,
				&size,
				&type,
				name
			);
			if (size > 1) 
			{
				for (int j = 0; j < size; j++) 
				{
					char long_name[64];
					sprintf(long_name, "%s[%i]", name, j);
					int location = glGetAttribLocation(program, long_name);
					logger.log("  %i) type:%s name:%s location:%i\n",
						i, glTypeToString(type), long_name, location);
				}
			}
			else 
			{
				int location = glGetAttribLocation(program, name);
				logger.log("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), name, location);
			}
		}

		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
		logger.log("GL_ACTIVE_UNIFORMS = %i\n", params);
		for (int i = 0; i < params; i++) 
		{
			char name[64];
			int max_length = 64;
			int actual_length = 0;
			int size = 0;
			GLenum type;
			glGetActiveUniform(
				program,
				i,
				max_length,
				&actual_length,
				&size,
				&type,
				name
			);
			if (size > 1) 
			{
				for (int j = 0; j < size; j++) 
				{
					char long_name[64];
					sprintf(long_name, "%s[%i]", name, j);
					int location = glGetUniformLocation(program, long_name);
					logger.log("  %i) type:%s name:%s location:%i\n",
						i, glTypeToString(type), long_name, location);
				}
			}
			else 
			{
				int location = glGetUniformLocation(program, name);
				logger.log("  %i) type:%s name:%s location:%i\n",
					i, glTypeToString(type), name, location);
			}
		}

		printProgramInfoToLog(program);
	}

	/* This is a very expensive operation, only use for debug */
	static bool isValid(GLuint program) 
	{
		glValidateProgram(program);
		int params = -1;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
		logger.log("program %i GL_VALIDATE_STATUS = %i\n", program, params);
		if (GL_TRUE != params) 
		{
			printProgramInfoToLog(program);
			return false;
		}
		return true;
	}

	Program::Program(Shader& vertexShader, Shader& fragmentShader)
	{
		logger.log("Building shader program...\n");
		vertexShaderId = vertexShader.getShaderId();
		fragmentShaderId = fragmentShader.getShaderId();
		programId = glCreateProgram();
		glAttachShader(programId, fragmentShader.getShaderId());
		glAttachShader(programId, vertexShader.getShaderId());
		glLinkProgram(programId);
		checkShaderProgramLinkingErrors(programId);
		isValid(programId);
	}

	GLuint Program::getVertexShaderId()
	{
		return vertexShaderId;
	}

	GLuint Program::getFragmentShaderId()
	{
		return fragmentShaderId;
	}

	GLuint Program::getProgramId() 
	{
		return programId;
	}

	void Program::use()
	{
		glUseProgram(programId);
	}

	void Program::setVector4f(const char* inputName, float x,float y,float z,float w)
	{
		GLint inputLocation = glGetUniformLocation(programId, inputName);
		glUniform4f(inputLocation, x, y, z, w);
	}

	void Program::setFloat(const char* inputName, float input)
	{
		GLint inputLocation = glGetUniformLocation(programId, inputName);
		assert(inputLocation != 0xFFFFFFFF);
		glUniform1f(inputLocation, input);
	}

	void Program::setMatrix4f(const char* inputName, Matrix4f inputMatrix)
	{
		GLint worldLocation = glGetUniformLocation(programId, inputName);
		glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &inputMatrix.m[0][0]);
	}
}