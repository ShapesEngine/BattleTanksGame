#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace Utils
{
	class ShaderHelper
	{
	public:
		static void SetBool( GLuint ID, const std::string& name, bool value );
		static void SetInt( GLuint ID, const std::string& name, int value );
		static void SetFloat( GLuint ID, const std::string& name, float value );
		static void SetVec2( GLuint ID, const std::string& name, const glm::vec2& value );
		static void SetVec2( GLuint ID, const std::string& name, float x, float y );
		static void SetVec3( GLuint ID, const std::string& name, const glm::vec3& value );
		static void SetVec3( GLuint ID, const std::string& name, float x, float y, float z );
		static void SetVec4( GLuint ID, const std::string& name, const glm::vec4& value );
		static void SetVec4( GLuint ID, const std::string& name, float x, float y, float z, float w );
		static void SetMat2( GLuint ID, const std::string& name, const glm::mat2& mat );
		static void SetMat3( GLuint ID, const std::string& name, const glm::mat3& mat );
		static void SetMat4( GLuint ID, const std::string& name, const glm::mat4& mat );
	};
}