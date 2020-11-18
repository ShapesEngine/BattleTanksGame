#include "Sprite.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "../Utils/ShaderHelper.h"
#include "Texture2D.h"

namespace Renderer
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

		glGenVertexArrays( 1, &VAO );
		glBindVertexArray( VAO );

		vertexCoordsBuffer.Init( vertexCoords, 2 * 4 * sizeof( GLfloat ) );

		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

		textureCoordsBuffer.Init( &textureCoords[0], 2 * 4 * sizeof( GLfloat ) );

		glEnableVertexAttribArray( 1 );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

		indicesBuffer.Init( vertexIndices, 6 * sizeof( GLuint ) );

		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );
	}

	Sprite::~Sprite()
	{
		glDeleteVertexArrays( 1, &VAO );
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

		glBindVertexArray( VAO );
		Utils::ShaderHelper::SetMat4( pShaderProgram->GetID(), "model", model );

		glActiveTexture( GL_TEXTURE0 );
		pTexture->Bind();

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
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
