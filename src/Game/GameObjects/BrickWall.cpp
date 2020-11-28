#include "BrickWall.h"

BrickWall::BrickWall( const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, float rotation ) :
	IGameObject( position, size, rotation ),
	pCurrentSprite( std::move( pSprite ) )
{}
