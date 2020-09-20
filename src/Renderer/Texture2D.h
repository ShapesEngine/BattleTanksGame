#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class Texture2D
	{
	public:
		Texture2D(GLuint width, GLuint height, unsigned char* data, GLuint channels = 4, GLenum filter = GL_NEAREST, GLenum wrappingFilter = GL_CLAMP_TO_EDGE);
		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&& tex) noexcept;
		~Texture2D();

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& tex) noexcept;

	public:
		inline void Bind() const { glBindTexture(GL_TEXTURE_2D, ID); }
		inline static void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	private:
		GLuint ID;
		GLenum format;
		GLuint width;
		GLuint height;
	};
}