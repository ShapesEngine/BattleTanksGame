#include "SpriteAnimator.h"
#include "Sprite.h"

RenderEngine::SpriteAnimator::SpriteAnimator( std::shared_ptr<Sprite> pSprite ) :
	pSprite( pSprite ),
	currentFrameDuration( pSprite->GetFrameDuration( 0 ) )
{}

void RenderEngine::SpriteAnimator::Update( uint64_t delta )
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
