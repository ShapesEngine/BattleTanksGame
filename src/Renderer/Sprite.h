#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

#include "../Utils/IndexBuffer.h"
#include "../Utils/VertexBuffer.h"
#include "../Utils/VertexArray.h"

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		Sprite( std::shared_ptr<Texture2D> pTexture,
				std::string initialSubTexture,
				std::shared_ptr<ShaderProgram> pShaderProgram );

		virtual void Render( const glm::vec2& position, const glm::vec2& size, float rotation ) const;

	protected:
		std::vector<GLfloat> GetSubTextureCoordinates( std::string initialSubTexture ) const;

		std::shared_ptr<Texture2D> pTexture;
		Utils::VertexBuffer textureCoordsBuffer;

	private:
		std::shared_ptr<ShaderProgram> pShaderProgram;

		Utils::VertexArray vertexArray;
		Utils::VertexBuffer vertexCoordsBuffer;	
		Utils::IndexBuffer indicesBuffer;			
	};
}