#include "Eagle.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Eagle::Eagle( const glm::vec2& position, const glm::vec2& size_in, float rotation, float depthLayer ) :
	IGameObject( position, size_in, rotation, depthLayer ),
	pSprites{ ResourceManager::GetSprite( "eagle" ), ResourceManager::GetSprite( "eagle_dead" ) },
	eCurrentState( EEagleState::Alive )
{	
	colliders.emplace_back( glm::vec2( 0 ), size );
}

void Eagle::Render() const
{
	pSprites[(size_t)( eCurrentState )]->Render( position, size, rotation, depthLayer );
}
