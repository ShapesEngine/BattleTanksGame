#include "BrickWall.h"

#include "../../Resources/ResourceManager.h"

BrickWall::BrickWall( EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size, float rotation ) :
	IGameObject( position, size, rotation ),
	eCurrentBrickState{ EBrickState::Destroyed,
						EBrickState::Destroyed,
						EBrickState::Destroyed,
						EBrickState::Destroyed }, 
	blockOffsets { glm::vec2( 0, size.y / 2.f ), 
                       glm::vec2( size.x / 2.f, size.y / 2.f ), 
                       glm::vec2( 0, 0 ), 
                       glm::vec2( size.x / 2.f, 0 ) }
{
	sprites[(int)EBrickState::All] = ResourceManager::GetSprite( "brickWall_All" );
	sprites[(int)EBrickState::TopLeft] = ResourceManager::GetSprite( "brickWall_TopLeft" );
	sprites[(int)EBrickState::TopRight] = ResourceManager::GetSprite( "brickWall_TopRight" );
	sprites[(int)EBrickState::Top] = ResourceManager::GetSprite( "brickWall_Top" );
	sprites[(int)EBrickState::BottomLeft] = ResourceManager::GetSprite( "brickWall_BottomLeft" );
	sprites[(int)EBrickState::Left] = ResourceManager::GetSprite( "brickWall_Left" );
	sprites[(int)EBrickState::TopRight_BottomLeft] = ResourceManager::GetSprite( "brickWall_TopRight_BottomLeft" );
	sprites[(int)EBrickState::Top_BottomLeft] = ResourceManager::GetSprite( "brickWall_Top_BottomLeft" );
	sprites[(int)EBrickState::BottomRight] = ResourceManager::GetSprite( "brickWall_BottomRight" );
	sprites[(int)EBrickState::TopLeft_BottomRight] = ResourceManager::GetSprite( "brickWall_TopLeft_BottomRight" );
	sprites[(int)EBrickState::Right] = ResourceManager::GetSprite( "brickWall_Right" );
	sprites[(int)EBrickState::Top_BottomRight] = ResourceManager::GetSprite( "brickWall_Top_BottomRight" );
	sprites[(int)EBrickState::Bottom] = ResourceManager::GetSprite( "brickWall_Bottom" );
	sprites[(int)EBrickState::TopLeft_Bottom] = ResourceManager::GetSprite( "brickWall_TopLeft_Bottom" );
	sprites[(int)EBrickState::TopRight_Bottom] = ResourceManager::GetSprite( "brickWall_TopRight_Bottom" );

	switch( eBrickWallType )
	{
	case EBrickWallType::All:
		eCurrentBrickState.fill( EBrickState::All );
		break;
	case EBrickWallType::Top:
		eCurrentBrickState[(int)EBrickLocation::TopLeft] = EBrickState::All;
		eCurrentBrickState[(int)EBrickLocation::TopRight] = EBrickState::All;
		break;
	case EBrickWallType::Bottom:
		eCurrentBrickState[(int)EBrickLocation::BottomLeft] = EBrickState::All;
		eCurrentBrickState[(int)EBrickLocation::BottomRight] = EBrickState::All;
		break;
	case EBrickWallType::Left:
		eCurrentBrickState[(int)EBrickLocation::TopLeft] = EBrickState::All;
		eCurrentBrickState[(int)EBrickLocation::BottomLeft] = EBrickState::All;
		break;
	case EBrickWallType::Right:
		eCurrentBrickState[(int)EBrickLocation::TopRight] = EBrickState::All;
		eCurrentBrickState[(int)EBrickLocation::BottomRight] = EBrickState::All;
		break;
	case EBrickWallType::TopLeft:
		eCurrentBrickState[(int)EBrickLocation::TopLeft] = EBrickState::All;
		break;
	case EBrickWallType::TopRight:
		eCurrentBrickState[(int)EBrickLocation::TopRight] = EBrickState::All;
		break;
	case EBrickWallType::BottomLeft:
		eCurrentBrickState[(int)EBrickLocation::BottomLeft] = EBrickState::All;
		break;
	case EBrickWallType::BottomRight:
		eCurrentBrickState[(int)EBrickLocation::BottomRight] = EBrickState::All;
		break;
	}
}

void BrickWall::Render() const
{
	RenderBrick( EBrickLocation::TopLeft );
	RenderBrick( EBrickLocation::TopRight );
	RenderBrick( EBrickLocation::BottomLeft );
	RenderBrick( EBrickLocation::BottomRight );
}

void BrickWall::RenderBrick( const EBrickLocation eBrickLocation ) const
{
	const EBrickState state = eCurrentBrickState[static_cast<size_t>( eBrickLocation )];
	if( state != EBrickState::Destroyed )
	{
		sprites[static_cast<size_t>( state )]->Render( position + blockOffsets[static_cast<size_t>( eBrickLocation )], size / 2.f, rotation );
	}
}
