#include "ConcreteWall.h"

#include "../../Resources/ResourceManager.h"

ConcreteWall::ConcreteWall( EConcreteWallType eConcreteWallType, const glm::vec2& position, const glm::vec2& size_in, float rotation, float depthLayer ) :
	IGameObject( position, size_in, rotation, depthLayer ),
	eCurrentBlockState{ EConcreteState::Destroyed,
						EConcreteState::Destroyed,
						EConcreteState::Destroyed,
						EConcreteState::Destroyed }, 
	pSprite( ResourceManager::GetSprite( "concreteWall" ) ),
	blockOffsets { glm::vec2( 0, size.y / 2.f ), 
                       glm::vec2( size.x / 2.f, size.y / 2.f ), 
                       glm::vec2( 0, 0 ), 
                       glm::vec2( size.x / 2.f, 0 ) }
{
	switch( eConcreteWallType )
	{
	case EConcreteWallType::All:
		eCurrentBlockState.fill( EConcreteState::Enabled );
		colliders.emplace_back( glm::vec2( 0 ), size );
		break;
	case EConcreteWallType::Top:
		eCurrentBlockState[(size_t)EConcreteLocation::TopLeft] = EConcreteState::Enabled;
		eCurrentBlockState[(size_t)EConcreteLocation::TopRight] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( 0, size.y / 2 ), size );
		break;
	case EConcreteWallType::Bottom:
		eCurrentBlockState[(size_t)EConcreteLocation::BottomLeft] = EConcreteState::Enabled;
		eCurrentBlockState[(size_t)EConcreteLocation::BottomRight] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( 0 ), glm::vec2( size.x, size.y / 2 ) );
		break;
	case EConcreteWallType::Left:
		eCurrentBlockState[(size_t)EConcreteLocation::TopLeft] = EConcreteState::Enabled;
		eCurrentBlockState[(size_t)EConcreteLocation::BottomLeft] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( 0 ), glm::vec2( size.x / 2, size.y ) );
		break;
	case EConcreteWallType::Right:
		eCurrentBlockState[(size_t)EConcreteLocation::TopRight] = EConcreteState::Enabled;
		eCurrentBlockState[(size_t)EConcreteLocation::BottomRight] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( size.x / 2, 0 ), size );
		break;
	case EConcreteWallType::TopLeft:
		eCurrentBlockState[(size_t)EConcreteLocation::TopLeft] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( 0, size.y / 2 ), glm::vec2( size.x / 2, size.y ) );
		break;
	case EConcreteWallType::TopRight:
		eCurrentBlockState[(size_t)EConcreteLocation::TopRight] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( size.x / 2, size.y / 2 ), size );
		break;
	case EConcreteWallType::BottomLeft:
		eCurrentBlockState[(size_t)EConcreteLocation::BottomLeft] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( 0 ), glm::vec2( size.x / 2, size.y / 2 ) );
		break;
	case EConcreteWallType::BottomRight:
		eCurrentBlockState[(size_t)EConcreteLocation::BottomRight] = EConcreteState::Enabled;
		colliders.emplace_back( glm::vec2( size.x / 2, 0 ), glm::vec2( size.x, size.y / 2 ) );
		break;
	}
}

void ConcreteWall::Render() const
{
	RenderBrick( EConcreteLocation::TopLeft );
	RenderBrick( EConcreteLocation::TopRight );
	RenderBrick( EConcreteLocation::BottomLeft );
	RenderBrick( EConcreteLocation::BottomRight );
}

void ConcreteWall::RenderBrick( const EConcreteLocation eBlockLocation ) const
{
	const EConcreteState state = eCurrentBlockState[static_cast<size_t>( eBlockLocation )];
	if( state != EConcreteState::Destroyed )
	{
		pSprite->Render( position + blockOffsets[static_cast<size_t>( eBlockLocation )], size / 2.f, rotation, depthLayer );
	}
}
