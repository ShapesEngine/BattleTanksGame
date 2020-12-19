#include "Border.h"

#include "../../Resources/ResourceManager.h"

Border::Border( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer ) :
	IGameObject( position, size, rotation, depthLayer ),
	pSprite( ResourceManager::GetSprite( "border" ) )
{
	colliders.emplace_back( glm::vec2( 0 ), size );
}

void Border::Render() const
{
	pSprite->Render( position, size, rotation, depthLayer );
}
