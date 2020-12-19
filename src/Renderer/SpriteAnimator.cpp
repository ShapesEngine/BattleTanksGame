#include "SpriteAnimator.h"
#include "Sprite.h"

RenderEngine::SpriteAnimator::SpriteAnimator( std::shared_ptr<Sprite> pSprite ) :
	pSprite( pSprite )
{
	Reset();

	for( size_t currentFrameId = 0; currentFrameId < pSprite->GetFramesCount(); ++currentFrameId )
	{
		totalDuration += pSprite->GetFrameDuration( currentFrameId );
	}
}

void RenderEngine::SpriteAnimator::Update( double delta )
{
	currentAnimationTime += delta;
	while( currentAnimationTime >= currentFrameDuration )
	{
		currentAnimationTime -= currentFrameDuration;
		++currentFrame;
		if( currentFrame == pSprite->GetFramesCount() )
		{
			currentFrame = 0;
		}
		currentFrameDuration = pSprite->GetFrameDuration( currentFrame );
	}
}

void RenderEngine::SpriteAnimator::Reset()
{
	currentFrame = 0;
	currentFrameDuration = pSprite->GetFrameDuration( 0 );
	currentAnimationTime = 0.0;
}
