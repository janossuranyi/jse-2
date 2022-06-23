
#include "graphics/ShaderProgram.hpp"
#include "core/io/Logger.hpp"
#include <vector>
#include <GL/glew.h>

namespace jse {

	const static int MAX_SHADER_SOURCES = 64;

	ShaderProgram::ShaderProgram()
	{
		program = GL_INVALID_INDEX;
		created = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		if (program != GL_INVALID_INDEX)
		{
			glDeleteProgram(program);
		}
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	{
		program = other.program;
		created = other.created;
		vs_source = other.vs_source;
		fs_source = other.fs_source;

		other.created = false;
		other.program = GL_INVALID_INDEX;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
	{
		program = other.program;
		created = other.created;
		vs_source = other.vs_source;
		fs_source = other.fs_source;

		other.created = false;
		other.program = GL_INVALID_INDEX;

		return *this;
	}

	bool ShaderProgram::Compile(std::string& _vserror, std::string& _fserror, std::string& _linkerror)
	{

		GLint result = GL_FALSE;

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);

		std::vector<const char*> srcPtrs;

		for (auto elem : vs_source)
		{
			srcPtrs.push_back(elem.c_str());
		}

		glShaderSource(vs, (GLsizei)srcPtrs.size(), srcPtrs.data(), nullptr);

		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint infologLen;
			glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infologLen);
			if (infologLen > 0) {
				std::vector<char> logBuf(infologLen);
				glGetShaderInfoLog(vs, infologLen, nullptr, logBuf.data());
				_vserror = logBuf.data();
			}

			glDeleteShader(vs);

			return false;
		}

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		
		srcPtrs.clear();
		for (auto elem : fs_source)
		{
			srcPtrs.push_back(elem.c_str());
		}

		glShaderSource(fs, (GLsizei)srcPtrs.size(), srcPtrs.data(), nullptr);

		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint infologLen;
			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infologLen);
			if (infologLen > 0) {
				std::vector<char> logBuf(infologLen);
				glGetShaderInfoLog(fs, infologLen, nullptr, logBuf.data());
				_fserror = logBuf.data();
			}

			glDeleteShader(vs);
			glDeleteShader(fs);

			return false;
		}

		GLuint p = glCreateProgram();

		glAttachShader(p, vs);
		glAttachShader(p, fs);

		glLinkProgram(p);

		glGetProgramiv(p, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint infologLen;
			glGetProgramiv(p, GL_INFO_LOG_LENGTH, &infologLen);
			if (infologLen > 0) {
				std::vector<char> logBuf(infologLen);
				_linkerror = logBuf.data();

				glDeleteShader(vs);
				glDeleteShader(fs);
				glDeleteProgram(p);

				return false;
			}
		}

		program = p;
		created = true;

		glDeleteShader(vs);
		glDeleteShader(fs);

		return true;

	}
	void ShaderProgram::SetFloat(const std::string& _name, float _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniform1f(loc, _x);
	}
	void ShaderProgram::SetInt(const std::string& _name, int _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniform1i(loc, _x);
	}
	void ShaderProgram::SetMatrix3(const std::string& _name, const float* _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniformMatrix3fv(loc, 1, GL_FALSE, _x);
	}
	void ShaderProgram::SetMatrix4(const std::string& _name, const float* _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniformMatrix4fv(loc, 1, GL_FALSE, _x);
	}
	void ShaderProgram::SetFloat3v(const std::string& _name, unsigned _count, const float* _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniform3fv(loc, _count, _x);
	}
	void ShaderProgram::SetFloat4v(const std::string& _name, unsigned _count, const float* _x)
	{
		GLint loc = glGetUniformLocation(program, _name.c_str());
		if (loc == -1) return;

		glUniform4fv(loc, _count, _x);
	}

	void ShaderProgram::SetFloat(int _name, float _x)
	{
		glUniform1f((GLint)_name, _x);
	}
	void ShaderProgram::SetInt(int _name, int _x)
	{
		glUniform1i((GLint)_name, _x);
	}
	void ShaderProgram::SetMatrix3(int _name, const float* _x)
	{
		glUniformMatrix3fv((GLint)_name, 1, GL_FALSE, _x);
	}
	void ShaderProgram::SetMatrix4(int _name, const float* _x)
	{
		glUniformMatrix4fv((GLint)_name, 1, GL_FALSE, _x);
	}
	void ShaderProgram::SetFloat3v(int _name, unsigned _count, const float* _x)
	{
		glUniform3fv((GLint)_name, _count, _x);
	}
	void ShaderProgram::SetFloat4v(int _name, unsigned _count, const float* _x)
	{
		glUniform4fv((GLint)_name, _count, _x);
	}

	void ShaderProgram::Bind()
	{
		if (program != GL_INVALID_INDEX)
		{
			glUseProgram(program);
		}
	}

	void ShaderProgram::BindUniformBlock(const std::string& _name, const int _bindingPoint)
	{
		GLuint block_index = glGetUniformBlockIndex(program, _name.c_str());

		if (GL_INVALID_INDEX == block_index) {
			Warning("Uniform  block '%s' not exists", _name.c_str());
			return;
		}

		glUniformBlockBinding(program, block_index, _bindingPoint);

	}

}