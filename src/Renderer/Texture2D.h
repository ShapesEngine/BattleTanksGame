#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RenderEngine
{
	class Texture2D
	{
	public:
		struct SubTexture2D
		{
			glm::vec2 leftBottomUV = glm::vec2( 0.f );
			glm::vec2 rightTopUV = glm::vec2( 1.f );

			SubTexture2D() = default;
			SubTexture2D( const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV )
				: leftBottomUV( _leftBottomUV )
				, rightTopUV( _rightTopUV )
			{}
		};

	public:
		Texture2D(GLuint width, GLuint height, unsigned char* data, GLuint channels = 4, GLenum filter = GL_NEAREST, GLenum wrappingFilter = GL_CLAMP_TO_EDGE);
		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&& tex) noexcept;
		~Texture2D();

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& tex) noexcept;

		void AddSubTexture( std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV );
		const SubTexture2D& GetSubTexture( const std::string& name ) const;

	public:
		inline void Bind() const { glBindTexture(GL_TEXTURE_2D, ID); }
		inline static void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

		uint32_t GetWidth() const { return width; }
		uint32_t GetHeight() const { return height; }

	private:
		GLuint ID;
		GLenum format;
		GLuint width;
		GLuint height;

		std::map<std::string, SubTexture2D> subTextures;
	};
}