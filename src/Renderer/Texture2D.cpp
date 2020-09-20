#include "Texture2D.h"
#include <utility>

Texture2D::Texture2D( GLuint width, GLuint height, unsigned char* data, GLuint channels, GLenum filter, GLenum wrappingFilter ) :
	width( width ),
	height( height ),
	format( channels == 3 ? GL_RGB : GL_RGBA )
{
	glGenTextures( 1, &ID );
	Bind();
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, wrappingFilter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, wrappingFilter );
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
