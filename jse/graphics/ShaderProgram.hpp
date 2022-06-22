#ifndef JSE_GRAPHICS_SHADER_PROGRAM_H
#define JSE_GRAPHICS_SHADER_PROGRAM_H

#include "core/Types.hpp"

namespace jse {

	enum shaderStage_t
	{
		ST_VERTEX,
		ST_FRAGMENT,
		ST_COMPUTE
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		// NOT COPIEABLE !
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&&) noexcept;

		ShaderProgram& operator=(ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) noexcept;

		void AddVertexSource(const std::string& _str) { vs_source.push_back(_str); };
		void AddFragmentSource(const std::string& _str) { fs_source.push_back(_str); };

		bool Compile(std::string& _vserror, std::string& _fserror, std::string& _linkerror);
		
		void SetFloat(const std::string& _name, float _x);
		void SetInt(const std::string& _name, int _x);

		void SetMatrix3(const std::string& _name, const float* _x);
		void SetMatrix4(const std::string& _name, const float* _x);
		void SetFloat3v(const std::string& _name, unsigned _count, const float* _x);
		void SetFloat4v(const std::string& _name, unsigned _count, const float* _x);

		void SetFloat(int _name, float _x);
		void SetInt(int _name, int _x);

		void SetMatrix3(int _name, const float* _x);
		void SetMatrix4(int _name, const float* _x);
		void SetFloat3v(int _name, unsigned _count, const float* _x);
		void SetFloat4v(int _name, unsigned _count, const float* _x);

		void Bind();

		void BindUniformBlock(const std::string& _name, const int _bindingPoint);

		unsigned int GetProgram() const { return program; };
	private:
		StrVec vs_source;
		StrVec fs_source;

		unsigned int program;
		bool created;
	};

}

#endif // !JSE_GRAPHICS_SHADER_PROGRAM_H
