#pragma once

#include <vector>
#include <glad/glad.h>

namespace Utils
{
	class VertexBufferLayout
	{
	public:
		struct VertexBufferLayoutElement
		{
			GLint count;
			GLenum type;
			GLboolean normalized;
			GLuint size;
		};

	public:
		VertexBufferLayout() = default;

		void AddElementLayoutFloat( GLuint count, bool normalized );

		inline void ReserveElements( const size_t count ) { layoutElments.reserve( count ); }
		inline GLuint GetStride() const { return stride; }		
		inline const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const { return layoutElments; }

	private:
		std::vector<VertexBufferLayoutElement> layoutElments;
		GLuint stride = 0;
	};
}