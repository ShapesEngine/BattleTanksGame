#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace Utils
{
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray( const VertexArray& ) = delete;		
		VertexArray( VertexArray&& vertexArray ) noexcept;
		VertexArray& operator=( const VertexArray& ) = delete;
		VertexArray& operator=( VertexArray&& vertexArray ) noexcept;
		~VertexArray();		

		void AddBuffer( const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout );

		inline void Bind() const { glBindVertexArray( id ); }
		inline void Unbind() const { glBindVertexArray( 0 ); }

	private:
		GLuint id = 0;
		uint32_t elementsCount = 0;
	};
}