#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer( const VertexBuffer& ) = delete;
		VertexBuffer& operator=( const VertexBuffer& ) = delete;
		VertexBuffer& operator=( VertexBuffer&& vertexBuffer ) noexcept;
		VertexBuffer( VertexBuffer&& vertexBuffer ) noexcept;
		~VertexBuffer();

		void Init( const void* data, GLuint size );
		void Update( const void* data, GLuint size ) const;

		inline void Bind() const { glBindBuffer( GL_ARRAY_BUFFER, id ); }
		inline static void Unbind() { glBindBuffer( GL_ARRAY_BUFFER, 0 ); }

	private:
		GLuint id = 0;
	};
}