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
				std::shared_ptr<ShaderProgram> pShaderProgram,
				const glm::vec2& position = glm::vec2( 0.f ),
				const glm::vec2& size = glm::vec2( 1.f ),
				float rotation = 0.f );

		virtual void Render() const;		

		inline void SetPosition( const glm::vec2& position_in ) { position = position_in; }
		inline void SetSize( const glm::vec2& size_in ) { size = size_in; }
		inline void SetRotation( float rotation_in ) { rotation = rotation_in; }

	protected:
		std::vector<GLfloat> GetSubTextureCoordinates( std::string initialSubTexture ) const;

		std::shared_ptr<Texture2D> pTexture;
		Utils::VertexBuffer textureCoordsBuffer;

	private:
		std::shared_ptr<ShaderProgram> pShaderProgram;
		glm::vec2 position;
		glm::vec2 size;
		float rotation;

		Utils::VertexArray vertexArray;
		Utils::VertexBuffer vertexCoordsBuffer;	
		Utils::IndexBuffer indicesBuffer;			
	};
}