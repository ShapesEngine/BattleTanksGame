#include "ShaderProgram.h"

#include <iostream>

namespace Renderer 
{
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID) != Status::OK)
			return;

		GLuint fragmentShaderID;
		if (CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID) != Status::OK)
		{
			glDeleteShader(vertexShaderID); // delete vertex shader, as if it was compiled it will continue consuming memory
			return;
		}

		LinkProgram(vertexShaderID, fragmentShaderID);
	}	

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(ID);
		ID = shaderProgram.ID;
		status = shaderProgram.status;

		shaderProgram.ID = 0;
		shaderProgram.status = Status::COMPILATION_ERROR;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		ID = shaderProgram.ID;
		status = shaderProgram.status;

		shaderProgram.ID = 0;
		shaderProgram.status = Status::COMPILATION_ERROR;
	}


	ShaderProgram::Status ShaderProgram::CreateShader( const std::string& source, const GLenum shaderType, GLuint& shaderID )
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		return CompileShader(shaderType, shaderID);		
	}

	ShaderProgram::Status ShaderProgram::CompileShader( const GLenum shaderType, GLuint shaderID )
	{
		glCompileShader( shaderID );

		GLint success;
		glGetShaderiv( shaderID, GL_COMPILE_STATUS, &success );
		if ( !success )
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog( shaderID, 1024, nullptr, infoLog );
			std::string shaderTypeStr = ( shaderType == GL_VERTEX_SHADER ? "VERTEX SHADER" : 
										( shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT SHADER" : "GEOMETRY SHADER" ) );
			std::cerr << shaderTypeStr << "::COMPILATION ERROR!\n";
			std::cerr << "INFO:\n" << infoLog << std::endl;
			status = Status::COMPILATION_ERROR;
		}
		return status = Status::OK;
	}

	ShaderProgram::Status ShaderProgram::LinkProgram( const GLuint& vertexShaderID, const GLuint& fragmentShaderID )
	{
		ID = glCreateProgram();
		glAttachShader( ID, vertexShaderID );
		glAttachShader( ID, fragmentShaderID );
		glLinkProgram( ID );

		GLint success;
		glGetProgramiv( ID, GL_LINK_STATUS, &success );
		if ( !success )
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog( ID, 1024, nullptr, infoLog );
			std::cerr << "SHADER PROGRAM::LINKING ERROR:\n" << infoLog << std::endl;
			status = Status::LINKING_ERROR;
		}
		else
			status = Status::OK;

		glDeleteShader( vertexShaderID );
		glDeleteShader( fragmentShaderID );

		return status;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram( ID );
	}	
}