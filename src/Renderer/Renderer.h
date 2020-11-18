#pragma once

#include "../Utils/VertexArray.h"
#include "../Utils/IndexBuffer.h"
#include "ShaderProgram.h"

#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void Draw( const Utils::VertexArray& vertexArray, const Utils::IndexBuffer& indexBuffer, const ShaderProgram& shader );

		inline static void SetClearColor( float r, float g, float b, float a ) { glClearColor( r, g, b, a ); }
		inline static void Clear() { glClear( GL_COLOR_BUFFER_BIT ); }
		inline static void SetViewport( uint32_t width, uint32_t height, uint32_t leftOffset = 0, uint32_t bottomOffset = 0 ) { glViewport( leftOffset, bottomOffset, width, height ); }
		inline static std::string GetRendererStr() { return reinterpret_cast<const char*>( glGetString( GL_RENDERER ) ); }
		inline static std::string GetVersionStr() { return reinterpret_cast<const char*>( glGetString( GL_VERSION ) ); }
	};
}