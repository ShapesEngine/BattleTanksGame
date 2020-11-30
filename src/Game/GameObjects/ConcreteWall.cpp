#include "ConcreteWall.h"

#include "../../Resources/ResourceManager.h"

ConcreteWall::ConcreteWall( EConcreteWallType eConcreteWallType, const glm::vec2& position, const glm::vec2& size, float rotation ) :
	IGameObject( position, size, rotation ),
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
		break;
	case EConcreteWallType::Top:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopLeft )] = EConcreteState::Enabled;
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopRight )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::Bottom:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomLeft )] = EConcreteState::Enabled;
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomRight )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::Left:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopLeft )] = EConcreteState::Enabled;
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomLeft )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::Right:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopRight )] = EConcreteState::Enabled;
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomRight )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::TopLeft:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopLeft )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::TopRight:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::TopRight )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::BottomLeft:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomLeft )] = EConcreteState::Enabled;
		break;
	case EConcreteWallType::BottomRight:
		eCurrentBlockState[static_cast<size_t>( EConcreteLocation::BottomRight )] = EConcreteState::Enabled;
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
		pSprite->Render( position + blockOffsets[static_cast<size_t>( eBlockLocation )], size / 2.f, rotation );
	}
}
