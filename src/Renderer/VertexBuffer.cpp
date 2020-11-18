#include "VertexBuffer.h"

namespace Renderer
{
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers( 1, &id );
	}

	void VertexBuffer::Init( const void* data, GLuint size )
	{
		glGenBuffers( 1, &id );
		glBindBuffer( GL_ARRAY_BUFFER, id );
		glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
	}

	void VertexBuffer::Update( const void* data, GLuint size ) const
	{
		glBindBuffer( GL_ARRAY_BUFFER, id );
		glBufferSubData( GL_ARRAY_BUFFER, 0, size, data );
	}

	VertexBuffer& VertexBuffer::operator=( VertexBuffer&& vertexBuffer ) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
		return *this;
	}

	VertexBuffer::VertexBuffer( VertexBuffer&& vertexBuffer ) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
	}
}
