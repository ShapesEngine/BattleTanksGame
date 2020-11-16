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

		auto subTexture = pTexture->GetSubTexture( std::move( initialSubTexture ) );
		GLfloat lbX = subTexture.leftBottomUV.x;
		GLfloat lbY = subTexture.leftBottomUV.y;
		GLfloat rtX = subTexture.rightTopUV.x;
		GLfloat rtY = subTexture.rightTopUV.y;
		const GLfloat textureCoords[] = {
			// U  V
			lbX, lbY,
			lbX, rtY,
			rtX, rtY,
			rtX, lbY
		};

		constexpr GLuint vertexIndices[] = {
			0, 1, 2,
			0, 3, 2
		};

		glGenBuffers( 1, &vertVBO );
		glGenBuffers( 1, &texVBO );
		glGenBuffers( 1, &indEBO );

		glBindBuffer( GL_ARRAY_BUFFER, vertVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertexCoords ), vertexCoords, GL_STATIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, texVBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof( textureCoords ), textureCoords, GL_STATIC_DRAW );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indEBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( vertexIndices ), vertexIndices, GL_STATIC_DRAW );

		glGenVertexArrays( 1, &VAO );
		glBindVertexArray( VAO );

		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vertVBO );
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

		glEnableVertexAttribArray( 1 );
		glBindBuffer( GL_ARRAY_BUFFER, texVBO );
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers( 1, &vertVBO );
		glDeleteBuffers( 1, &texVBO );
		glDeleteBuffers( 1, &indEBO );
		glDeleteVertexArrays( 1, &VAO );
	}

	void Sprite::Render()
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

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indEBO );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
	}
}
