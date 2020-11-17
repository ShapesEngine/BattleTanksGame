#include "AnimatedSprite.h"

#include <iostream>

namespace Renderer
{
	void AnimatedSprite::SetAnimation( const std::string& animName )
	{
		if( itCurrentAnimFrame != animFrames.end() && animName == itCurrentAnimFrame->first )
		{
			return;
		}

		const auto it = animFrames.find( animName );
		if( it == animFrames.end() )
		{
			std::cerr << "ERROR::SetAnimation:: " << "Animation Frame not found!\n";
			return;
		}

		itCurrentAnimFrame = it;
		currentFrameIndex = 0;
		currentFrameTime = 0;
		isCurrentAnimFrameChanged = true;
	}

	void AnimatedSprite::Update( size_t deltaTime )
	{
		if( itCurrentAnimFrame == animFrames.end() )
		{
			return;
		}

		currentFrameTime += deltaTime;
		uint64_t frameTime = itCurrentAnimFrame->second[currentFrameIndex].second;
		while( currentFrameTime >= frameTime )
		{
			currentFrameTime -= frameTime;
			currentFrameIndex++;
			isCurrentAnimFrameChanged = true;
			if( currentFrameIndex == itCurrentAnimFrame->second.size() )
			{
				currentFrameIndex = 0;
			}
		}
	}

	void AnimatedSprite::Render() const
	{
		if( isCurrentAnimFrameChanged )
		{
			const std::vector<GLfloat> textureCoords = std::move( GetSubTextureCoordinates( itCurrentAnimFrame->second[currentFrameIndex].first ) );
			glBindBuffer( GL_ARRAY_BUFFER, texVBO );
			// Update current buffer
			glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( textureCoords ), &textureCoords[0] );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );

			isCurrentAnimFrameChanged = false;
		}

		Sprite::Render();
	}
}