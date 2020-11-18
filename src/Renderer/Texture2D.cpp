#include "Texture2D.h"

namespace RenderEngine
{
	Texture2D::Texture2D( GLuint width, GLuint height, unsigned char* data, GLuint channels, GLenum filter, GLenum wrappingFilter ) :
		width( width ),
		height( height ),
		format( channels == 3 ? GL_RGB : GL_RGBA )
	{
		glGenTextures( 1, &ID );
		glActiveTexture( GL_TEXTURE0 );
		Bind();
		glTexImage2D( GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingFilter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingFilter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
		glGenerateMipmap( GL_TEXTURE_2D );

		Unbind();
	}

	Texture2D::Texture2D( Texture2D&& tex ) noexcept :
		width( tex.width ),
		height( tex.height ),
		ID( tex.ID ),
		format( tex.format )
	{
		tex.ID = 0;
	}

	Texture2D::~Texture2D()
	{
		Unbind();
		glDeleteTextures( 1, &ID );
	}

	Texture2D& Texture2D::operator=( Texture2D&& tex ) noexcept
	{
		glDeleteTextures( 1, &tex.ID );
		width = tex.width;
		height = tex.height;
		ID = tex.ID;
		format = tex.format;

		tex.ID = 0;

		return *this;
	}

	void Texture2D::AddSubTexture( std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV )
	{
		subTextures.emplace( std::move( name ), SubTexture2D( leftBottomUV, rightTopUV ) );
	}

	const Texture2D::SubTexture2D& Texture2D::GetSubTexture( const std::string & name ) const
	{
		auto it = subTextures.find( name );
		if( it != subTextures.end() )
		{
			return it->second;
		}
		const static SubTexture2D defaultSubTexture;
		return defaultSubTexture;
	}
}
