#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class ShaderProgram
	{
	private:
		enum class Status : GLuint
		{
			OK,
			COMPILATION_ERROR,
			LINKING_ERROR
		};

	public:
		ShaderProgram( const std::string& vertexShader, const std::string& fragmentShader );		
		ShaderProgram() = delete;
		ShaderProgram( const ShaderProgram& ) = delete;		
		ShaderProgram( ShaderProgram&& shaderProgram ) noexcept;
		~ShaderProgram();

		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

	private:
		Status CreateShader( const std::string& source, const GLenum shaderType, GLuint& shaderID );
		Status CompileShader( const GLenum shaderType, GLuint shaderID );
		Status LinkProgram(const GLuint& vertexShaderID, const GLuint& fragmentShaderID);


	public:
		inline Status GetStatus() const { return status; }
		inline void Use() const { glUseProgram( ID ); }
		inline static void Disuse() { glUseProgram( 0 ); }

	private:
		Status status = Status::OK;
		GLuint ID = 0;
	};
}