#include "BrickWall.h"
#include "Bullet.h"

#include "../../Resources/ResourceManager.h"

BrickWall::BrickWall( EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size_in, float rotation, float depthLayer ) :
	IGameObject( position, size_in, rotation, depthLayer ),
	eCurrentBrickState{ EBrickState::Destroyed,
						EBrickState::Destroyed,
						EBrickState::Destroyed,
						EBrickState::Destroyed }, 
	blockOffsets { glm::vec2( 0, size.y / 2.f ), 
                       glm::vec2( size.x / 2.f, size.y / 2.f ), 
                       glm::vec2( 0, 0 ), 
                       glm::vec2( size.x / 2.f, 0 ) }
{
	sprites[(size_t)EBrickState::All] = ResourceManager::GetSprite( "brickWall_All" );
	sprites[(size_t)EBrickState::TopLeft] = ResourceManager::GetSprite( "brickWall_TopLeft" );
	sprites[(size_t)EBrickState::TopRight] = ResourceManager::GetSprite( "brickWall_TopRight" );
	sprites[(size_t)EBrickState::Top] = ResourceManager::GetSprite( "brickWall_Top" );
	sprites[(size_t)EBrickState::BottomLeft] = ResourceManager::GetSprite( "brickWall_BottomLeft" );
	sprites[(size_t)EBrickState::Left] = ResourceManager::GetSprite( "brickWall_Left" );
	sprites[(size_t)EBrickState::TopRight_BottomLeft] = ResourceManager::GetSprite( "brickWall_TopRight_BottomLeft" );
	sprites[(size_t)EBrickState::Top_BottomLeft] = ResourceManager::GetSprite( "brickWall_Top_BottomLeft" );
	sprites[(size_t)EBrickState::BottomRight] = ResourceManager::GetSprite( "brickWall_BottomRight" );
	sprites[(size_t)EBrickState::TopLeft_BottomRight] = ResourceManager::GetSprite( "brickWall_TopLeft_BottomRight" );
	sprites[(size_t)EBrickState::Right] = ResourceManager::GetSprite( "brickWall_Right" );
	sprites[(size_t)EBrickState::Top_BottomRight] = ResourceManager::GetSprite( "brickWall_Top_BottomRight" );
	sprites[(size_t)EBrickState::Bottom] = ResourceManager::GetSprite( "brickWall_Bottom" );
	sprites[(size_t)EBrickState::TopLeft_Bottom] = ResourceManager::GetSprite( "brickWall_TopLeft_Bottom" );
	sprites[(size_t)EBrickState::TopRight_Bottom] = ResourceManager::GetSprite( "brickWall_TopRight_Bottom" );

	auto onCollisionCallbackTopLeft = [&]( const IGameObject* object, const Physics::ECollisionDirection direction )
	{
		OnCollisionCallback( EBrickLocation::TopLeft, object, direction );
	};
	auto onCollisionCallbackTopRight = [&]( const IGameObject* object, const Physics::ECollisionDirection direction )
	{
		OnCollisionCallback( EBrickLocation::TopRight, object, direction );
	};
	auto onCollisionCallbackBottomLeft = [&]( const IGameObject* object, const Physics::ECollisionDirection direction )
	{
		OnCollisionCallback( EBrickLocation::BottomLeft, object, direction );
	};
	auto onCollisionCallbackBottomRight = [&]( const IGameObject* object, const Physics::ECollisionDirection direction )
	{
		OnCollisionCallback( EBrickLocation::BottomRight, object, direction );
	};
	brickLocationToColliderMap.fill( nullptr );
	colliders.reserve( 4 );

	switch( eBrickWallType )
	{
	case EBrickWallType::All:
		eCurrentBrickState.fill( EBrickState::All );
		brickLocationToColliderMap[(size_t)EBrickLocation::TopLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopLeft, EBrickState::All, size ), onCollisionCallbackTopLeft ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::TopRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopRight, EBrickState::All, size ), onCollisionCallbackTopRight ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomLeft, EBrickState::All, size ), onCollisionCallbackBottomLeft ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomRight, EBrickState::All, size ), onCollisionCallbackBottomRight ) );
		break;
	case EBrickWallType::Top:
		eCurrentBrickState[(size_t)EBrickLocation::TopLeft] = EBrickState::All;
		eCurrentBrickState[(size_t)EBrickLocation::TopRight] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::TopLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopLeft, EBrickState::All, size ), onCollisionCallbackTopLeft ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::TopRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopRight, EBrickState::All, size ), onCollisionCallbackTopRight ) );
		break;
	case EBrickWallType::Bottom:
		eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] = EBrickState::All;
		eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomLeft, EBrickState::All, size ), onCollisionCallbackBottomLeft ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomRight, EBrickState::All, size ), onCollisionCallbackBottomRight ) );
		break;
	case EBrickWallType::Left:
		eCurrentBrickState[(size_t)EBrickLocation::TopLeft] = EBrickState::All;
		eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::TopLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopLeft, EBrickState::All, size ), onCollisionCallbackTopLeft ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomLeft, EBrickState::All, size ), onCollisionCallbackBottomLeft ) );
		break;
	case EBrickWallType::Right:
		eCurrentBrickState[(size_t)EBrickLocation::TopRight] = EBrickState::All;
		eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::TopRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopRight, EBrickState::All, size ), onCollisionCallbackTopRight ) );
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomRight, EBrickState::All, size ), onCollisionCallbackBottomRight ) );
		break;
	case EBrickWallType::TopLeft:
		eCurrentBrickState[(size_t)EBrickLocation::TopLeft] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::TopLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopLeft, EBrickState::All, size ), onCollisionCallbackTopLeft ) );
		break;
	case EBrickWallType::TopRight:
		eCurrentBrickState[(size_t)EBrickLocation::TopRight] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::TopRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::TopRight, EBrickState::All, size ), onCollisionCallbackTopRight ) );
		break;
	case EBrickWallType::BottomLeft:
		eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomLeft] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomLeft, EBrickState::All, size ), onCollisionCallbackBottomLeft ) );
		break;
	case EBrickWallType::BottomRight:
		eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
		brickLocationToColliderMap[(size_t)EBrickLocation::BottomRight] = &( colliders.emplace_back( GetAABBForBrickState( EBrickLocation::BottomRight, EBrickState::All, size ), onCollisionCallbackBottomRight ) );
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
	const EBrickState state = eCurrentBrickState[(size_t)( eBrickLocation )];
	if( state != EBrickState::Destroyed )
	{
		sprites[(size_t)( state )]->Render( position + blockOffsets[(size_t)( eBrickLocation )], size / 2.f, rotation, depthLayer );
	}
}

BrickWall::EBrickState BrickWall::GetBrickStateAfterCollision( EBrickState currentState, Physics::ECollisionDirection direction )
{
	switch( currentState )
	{
	case EBrickState::All:
		switch( direction )
		{
		case Physics::ECollisionDirection::Left:
			return EBrickState::Right;
		case Physics::ECollisionDirection::Right:
			return EBrickState::Left;
		case Physics::ECollisionDirection::Top:
			return EBrickState::Bottom;
		case Physics::ECollisionDirection::Bottom:
			return EBrickState::Top;
		}

	case EBrickState::Top:
		switch( direction )
		{
		case Physics::ECollisionDirection::Left:
			return EBrickState::TopRight;
		case Physics::ECollisionDirection::Right:
			return EBrickState::TopLeft;
		case Physics::ECollisionDirection::Top:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Bottom:
			return EBrickState::Destroyed;
		}

	case EBrickState::Bottom:
		switch( direction )
		{
		case Physics::ECollisionDirection::Left:
			return EBrickState::BottomRight;
		case Physics::ECollisionDirection::Right:
			return EBrickState::BottomLeft;
		case Physics::ECollisionDirection::Top:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Bottom:
			return EBrickState::Destroyed;
		}

	case EBrickState::Left:
		switch( direction )
		{
		case Physics::ECollisionDirection::Left:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Right:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Top:
			return EBrickState::BottomLeft;
		case Physics::ECollisionDirection::Bottom:
			return EBrickState::TopLeft;
		}

	case EBrickState::Right:
		switch( direction )
		{
		case Physics::ECollisionDirection::Left:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Right:
			return EBrickState::Destroyed;
		case Physics::ECollisionDirection::Top:
			return EBrickState::BottomRight;
		case Physics::ECollisionDirection::Bottom:
			return EBrickState::TopRight;
		}

	default:
		return EBrickState::Destroyed;
	}
}

Physics::AABB BrickWall::GetAABBForBrickState( EBrickLocation location, EBrickState eBrickState, const glm::vec2& size )
{
	glm::vec2 blockOffset( 0.f );
	switch( location )
	{
	case EBrickLocation::BottomLeft:
		break;
	case EBrickLocation::BottomRight:
		blockOffset.x += size.x / 2.f;
		break;
	case EBrickLocation::TopLeft:
		blockOffset.y += size.y / 2.f;
		break;
	case EBrickLocation::TopRight:
		blockOffset += size / 2.f;
		break;
	}

	glm::vec2 bottomLeft( 0.f );
	glm::vec2 topRight( 0.f );
	switch( eBrickState )
	{
	case EBrickState::All:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::TopLeft:
		bottomLeft = glm::vec2( 0.f, size.y / 4.f );
		topRight = glm::vec2( size.x / 4, size.y / 2.f );
		break;
	case EBrickState::TopRight:
		bottomLeft = glm::vec2( size.x / 4.f, size.y / 4.f );
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Top:
		bottomLeft = glm::vec2( 0.f, size.y / 4.f );
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::BottomLeft:
		topRight = glm::vec2( size.x / 4.f, size.y / 4.f );
		break;
	case EBrickState::Left:
		topRight = glm::vec2( size.x / 4.f, size.y / 2.f );
		break;
	case EBrickState::TopRight_BottomLeft:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Top_BottomLeft:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::BottomRight:
		bottomLeft = glm::vec2( size.x / 4.f, 0.f );
		topRight = glm::vec2( size.x / 2.f, size.y / 4.f );
		break;
	case EBrickState::TopLeft_BottomRight:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Right:
		bottomLeft = glm::vec2( size.x / 4.f, 0.f );
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Top_BottomRight:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Bottom:
		topRight = glm::vec2( size.x / 2.f, size.y / 4.f );
		break;
	case EBrickState::TopLeft_Bottom:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::TopRight_Bottom:
		topRight = glm::vec2( size.x / 2.f, size.y / 2.f );
		break;
	case EBrickState::Destroyed:
		break;
	}

	return { bottomLeft + blockOffset, topRight + blockOffset };
}

void BrickWall::OnCollisionCallback( EBrickLocation location, const IGameObject* object, Physics::ECollisionDirection direction )
{
	Bullet* bullet = dynamic_cast<Bullet*>( const_cast<IGameObject*>( object ) );
	if( nullptr == bullet )
	{
		return;
	}
	const EBrickState newBrickState = GetBrickStateAfterCollision( eCurrentBrickState[(size_t)location], direction );
	eCurrentBrickState[(size_t)( location )] = newBrickState;
	if( newBrickState != EBrickState::Destroyed )
	{
		brickLocationToColliderMap[(size_t)location]->boundingBox = GetAABBForBrickState( location, newBrickState, size );
	}
	else
	{
		brickLocationToColliderMap[(size_t)location]->isActive = false;
	}
}
