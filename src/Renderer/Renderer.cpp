#include "Renderer.h"

namespace RenderEngine
{
	void Renderer::Draw( const Utils::VertexArray& vertexArray, const Utils::IndexBuffer& indexBuffer, const ShaderProgram& shader )
	{
		shader.Use();
		vertexArray.Bind();
		indexBuffer.Bind();

		glDrawElements( GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr );
	}
}
