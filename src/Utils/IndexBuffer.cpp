#include "IndexBuffer.h"

namespace Utils
{
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers( 1, &id );
	}

	void IndexBuffer::Init( const void* data, GLuint size )
	{
		glGenBuffers( 1, &id );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
	}

	void IndexBuffer::Update( const void* data, GLuint size ) const
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id );
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, size, data );
	}

	IndexBuffer& IndexBuffer::operator=( IndexBuffer&& vertexBuffer ) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
		return *this;
	}

	IndexBuffer::IndexBuffer( IndexBuffer&& vertexBuffer ) noexcept
	{
		id = vertexBuffer.id;
		vertexBuffer.id = 0;
	}
}
