#pragma once

#include <glad/glad.h>

namespace Utils
{
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer( const IndexBuffer& ) = delete;
		IndexBuffer& operator=( const IndexBuffer& ) = delete;
		IndexBuffer& operator=( IndexBuffer&& indicesBuffer ) noexcept;
		IndexBuffer( IndexBuffer&& indicesBuffer ) noexcept;
		~IndexBuffer();

		void Init( const void* data, GLuint count_in );

		inline void Bind() const { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id ); }
		inline static void Unbind() { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); }
		inline GLuint GetCount() const { return count; }

	private:
		GLuint id = 0;
		GLuint count = 0;
	};
}