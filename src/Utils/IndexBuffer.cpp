#include "IndexBuffer.h"

namespace Utils
{
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers( 1, &id );
	}

	void IndexBuffer::Init( const void* data, GLuint count_in )
	{
		count = count_in;
		glGenBuffers( 1, &id );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW );
	}

	void IndexBuffer::Update( const void* data, GLuint size ) const
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id );
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, size, data );
	}

	IndexBuffer& IndexBuffer::operator=( IndexBuffer&& indicesBuffer ) noexcept
	{
		id = indicesBuffer.id;
		indicesBuffer.id = 0;
		count = indicesBuffer.count;
		indicesBuffer.count = 0;
		return *this;
	}

	IndexBuffer::IndexBuffer( IndexBuffer&& indicesBuffer ) noexcept
	{
		id = indicesBuffer.id;
		indicesBuffer.id = 0;
		count = indicesBuffer.count;
		indicesBuffer.count = 0;
	}
}
