#include "Water.h"

#include "../../Resources/ResourceManager.h"
#include "../../Game/GameObjects/Bullet.h"

Water::Water( const glm::vec2& position, const glm::vec2& size_in, float rotation, float depthLayer ) :
	IGameObject( position, size_in, rotation, depthLayer ),
	pSprite( ResourceManager::GetSprite( "water" ) ),
	spriteAnim( pSprite ),
	blockOffsets{ glm::vec2( 0, size.y / 2.f ), 
                       glm::vec2( size.x / 2.f, size.y / 2.f ), 
                       glm::vec2( 0, 0 ), 
                       glm::vec2( size.x / 2.f, 0 ) }
{
	collidable = false;
	colliders.emplace_back( glm::vec2( 0 ), size );
}

void Water::Render() const
{
	RenderBrick( EBlockLocation::TopLeft );
	RenderBrick( EBlockLocation::TopRight );
	RenderBrick( EBlockLocation::BottomLeft );
	RenderBrick( EBlockLocation::BottomRight );
}

bool Water::IsCollidableWithSecondObject( const IGameObject* obj ) const
{
	Bullet* bullet = dynamic_cast<Bullet*>( const_cast<IGameObject*>( obj ) );
	if( nullptr != bullet )
	{
		return false;
	}
	return true;
}

void Water::RenderBrick( const EBlockLocation eBlockLocation ) const
{
	pSprite->Render( position + blockOffsets[(size_t)eBlockLocation], size / 2.f, rotation, depthLayer, spriteAnim.GetCurrentFrame() );
}
