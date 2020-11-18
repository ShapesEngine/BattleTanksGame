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
		IndexBuffer& operator=( IndexBuffer&& vertexBuffer ) noexcept;
		IndexBuffer( IndexBuffer&& vertexBuffer ) noexcept;
		~IndexBuffer();

		void Init( const void* data, GLuint size );
		void Update( const void* data, GLuint size ) const;

		inline void Bind() const { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id ); }
		inline static void Unbind() { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); }

	private:
		GLuint id = 0;
	};
}