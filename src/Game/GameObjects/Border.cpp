#include "Border.h"

#include "../../Resources/ResourceManager.h"

Border::Border( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer ) :
	IGameObject( position, size, rotation, depthLayer ),
	pSprite( ResourceManager::GetSprite( "border" ) )
{
	
}

void Border::Render() const
{
	pSprite->Render( position, size, rotation, depthLayer );
}
