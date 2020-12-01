#include "Ice.h"

#include "../../Resources/ResourceManager.h"

Ice::Ice( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer ) :
	IGameObject( position, size, rotation, depthLayer ),
	pSprite( ResourceManager::GetSprite( "ice" ) ),
	blockOffsets { glm::vec2( 0, size.y / 2.f ), 
                       glm::vec2( size.x / 2.f, size.y / 2.f ), 
                       glm::vec2( 0, 0 ), 
                       glm::vec2( size.x / 2.f, 0 ) }
{
	
}

void Ice::Render() const
{
	RenderBrick( EBlockLocation::TopLeft );
	RenderBrick( EBlockLocation::TopRight );
	RenderBrick( EBlockLocation::BottomLeft );
	RenderBrick( EBlockLocation::BottomRight );
}

void Ice::RenderBrick( const EBlockLocation eBlockLocation ) const
{
	pSprite->Render( position + blockOffsets[(size_t)eBlockLocation], size / 2.f, rotation, depthLayer );
}
