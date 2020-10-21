#include "ShaderHelper.h"

#include <cassert>

namespace Utils
{
	void ShaderHelper::SetBool( GLuint ID, const std::string& name, bool value )
	{
		assert( ID != 0 );
		glUniform1i( glGetUniformLocation( ID, name.c_str() ), (int) value );
	}

	void ShaderHelper::SetInt( GLuint ID, const std::string& name, int value )
	{
		assert( ID != 0 );
		glUniform1i( glGetUniformLocation( ID, name.c_str() ), value );
	}

	void ShaderHelper::SetFloat( GLuint ID, const std::string& name, float value )
	{
		assert( ID != 0 );
		glUniform1f( glGetUniformLocation( ID, name.c_str() ), value );
	}

	void ShaderHelper::SetVec2( GLuint ID, const std::string& name, const glm::vec2& value )
	{
		assert( ID != 0 );
		glUniform2fv( glGetUniformLocation( ID, name.c_str() ), 1, &value[0] );
	}
	void ShaderHelper::SetVec2( GLuint ID, const std::string& name, float x, float y )
	{
		assert( ID != 0 );
		glUniform2f( glGetUniformLocation( ID, name.c_str() ), x, y );
	}

	void ShaderHelper::SetVec3( GLuint ID, const std::string& name, const glm::vec3& value )
	{
		assert( ID != 0 );
		glUniform3fv( glGetUniformLocation( ID, name.c_str() ), 1, &value[0] );
	}
	void ShaderHelper::SetVec3( GLuint ID, const std::string& name, float x, float y, float z )
	{
		assert( ID != 0 );
		glUniform3f( glGetUniformLocation( ID, name.c_str() ), x, y, z );
	}

	void ShaderHelper::SetVec4( GLuint ID, const std::string& name, const glm::vec4& value )
	{
		assert( ID != 0 );
		glUniform4fv( glGetUniformLocation( ID, name.c_str() ), 1, &value[0] );
	}
	void ShaderHelper::SetVec4( GLuint ID, const std::string& name, float x, float y, float z, float w )
	{
		assert( ID != 0 );
		glUniform4f( glGetUniformLocation( ID, name.c_str() ), x, y, z, w );
	}

	void ShaderHelper::SetMat2( GLuint ID, const std::string& name, const glm::mat2& mat )
	{
		assert( ID != 0 );
		glUniformMatrix2fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
	}

	void ShaderHelper::SetMat3( GLuint ID, const std::string& name, const glm::mat3& mat )
	{
		assert( ID != 0 );
		glUniformMatrix3fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
	}

	void ShaderHelper::SetMat4( GLuint ID, const std::string& name, const glm::mat4& mat )
	{
		assert( ID != 0 );
		glUniformMatrix4fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
	}
}