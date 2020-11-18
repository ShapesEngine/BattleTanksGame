#include "VertexArray.h"

namespace Utils
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays( 1, &id );
	}

	VertexArray::VertexArray( VertexArray&& vertexArray ) noexcept
	{
		id = vertexArray.id;
		vertexArray.id = 0;
	}

	VertexArray& VertexArray::operator=( VertexArray && vertexArray ) noexcept
	{
		id = vertexArray.id;
		vertexArray.id = 0;
		return *this;
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays( 1, &id );
	}

	void VertexArray::AddBuffer( const VertexBuffer & vertexBuffer, const VertexBufferLayout & layout )
	{
		Bind();
		vertexBuffer.Bind();
		const auto& layoutElements = layout.GetLayoutElements();
		GLbyte* offset = nullptr;
		for( unsigned int i = 0; i < layoutElements.size(); ++i )
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = elementsCount + i;
			glEnableVertexAttribArray( currentAttribIndex );
			glVertexAttribPointer( currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.GetStride(), offset );
			offset += currentLayoutElement.size;
		}
		elementsCount += uint32_t( layoutElements.size() );
	}
}
