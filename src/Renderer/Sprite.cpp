#include "Sprite.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "../Utils/ShaderHelper.h"
#include "Texture2D.h"

namespace RenderEngine
{
	Sprite::Sprite( std::shared_ptr<Texture2D> pTexture_in,
					std::string initialSubTexture,
					std::shared_ptr<ShaderProgram> pShaderProgram,
					const glm::vec2& position,
					const glm::vec2& size,
					float rotation ) :
		pTexture( std::move( pTexture_in ) ),
		pShaderProgram( std::move( pShaderProgram ) ),
		position(position),
		size(size),
		rotation(rotation)
	{
		// =======================================================================
		// 2--3    3
		// | /   / |
		// 1    1--4
		// -----------------------------------------------------------------------
		constexpr GLfloat vertexCoords[] = {
			// X  Y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f
		};

		constexpr GLuint vertexIndices[] = {
			0, 1, 2,
			0, 3, 2
		};

		const std::vector<GLfloat> textureCoords = std::move( GetSubTextureCoordinates( std::move( initialSubTexture ) ) );	

		vertexCoordsBuffer.Init( vertexCoords, 2 * 4 * sizeof( GLfloat ) );

		Utils::VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.AddElementLayoutFloat( 2, false );
		vertexArray.AddBuffer( vertexCoordsBuffer, vertexCoordsLayout );

		textureCoordsBuffer.Init( &textureCoords[0], 2 * 4 * sizeof( GLfloat ) );

		Utils::VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.AddElementLayoutFloat( 2, false );
		vertexArray.AddBuffer( textureCoordsBuffer, textureCoordsLayout );

		indicesBuffer.Init( vertexIndices, 6 * sizeof( GLuint ) );

		vertexArray.Unbind();
		indicesBuffer.Unbind();
	}

	void Sprite::Render() const
	{
		pShaderProgram->Use();
		
		glm::mat4 model( 1.f );

		model = glm::translate( model, glm::vec3( position, 0.f ) );							// /\ to top		
		model = glm::translate( model, glm::vec3( 0.5f * size.x, 0.5f * size.y, 0.f ) );		// ||
		model = glm::rotate( model, glm::radians( rotation ), glm::vec3( 0.f, 0.f, 1.f ) );		// ||		
		model = glm::translate( model, glm::vec3( -0.5f * size.x, -0.5f * size.y, 0.f ) );		// ||	
		model = glm::scale( model, glm::vec3( size, 1.f ) );									// || from bottom

		vertexArray.Bind();
		Utils::ShaderHelper::SetMat4( pShaderProgram->GetID(), "model", model );

		glActiveTexture( GL_TEXTURE0 );
		pTexture->Bind();

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
		vertexArray.Unbind();
	}

	std::vector<GLfloat> Sprite::GetSubTextureCoordinates( std::string initialSubTexture ) const
	{
		auto subTexture = pTexture->GetSubTexture( std::move( initialSubTexture ) );
		GLfloat lbX = subTexture.leftBottomUV.x;
		GLfloat lbY = subTexture.leftBottomUV.y;
		GLfloat rtX = subTexture.rightTopUV.x;
		GLfloat rtY = subTexture.rightTopUV.y;
		std::vector<GLfloat> textureCoords = {
			// U  V
			lbX, lbY,
			lbX, rtY,
			rtX, rtY,
			rtX, lbY
		};

		return std::move( textureCoords );
	}
}
