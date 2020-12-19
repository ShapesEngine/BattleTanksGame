#include "Tank.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Tank::Tank(	float maxVelocity, const glm::vec2& position, const glm::vec2& size, float depthLayer ) :
	IGameObject( position, size, 0.f, depthLayer ),
	pSprite_top( ResourceManager::GetSprite( "TankSprite_Top" ) ),
	pSprite_bottom( ResourceManager::GetSprite( "TankSprite_Bottom" ) ),
	pSprite_left( ResourceManager::GetSprite( "TankSprite_Left" )),
	pSprite_right( ResourceManager::GetSprite( "TankSprite_Right" ) ),
	spriteAnimator_top( pSprite_top ),
	spriteAnimator_bottom( pSprite_bottom ),
	spriteAnimator_left( pSprite_left ),
	spriteAnimator_right( pSprite_right ),
	pSprite_respawn( ResourceManager::GetSprite( "respawn" ) ),
	spriteAnimator_respawn( pSprite_respawn ),
	pSprite_shield( ResourceManager::GetSprite( "shield" ) ),
	spriteAnimator_shield( pSprite_shield ),
	maxVelocity( maxVelocity )
{
	respawnTimer.SetCallback( [&]()
	{
		isSpawning = false;
		hasShield = true;
		shieldTimer.Start( 2000.0 );
	} );
	respawnTimer.Start( 1500.0 );
	shieldTimer.SetCallback( [&]() { hasShield = false; } );

	colliders.emplace_back( glm::vec2( 0 ), size );
}

void Tank::Render() const
{
	if( isSpawning )
	{
		pSprite_respawn->Render( position, size, rotation, 0.f, spriteAnimator_respawn.GetCurrentFrame() );
	}
	else
	{
		switch( eOrientation )
		{
		case Tank::EOrientation::Top:
			pSprite_top->Render( position, size, rotation, depthLayer, spriteAnimator_top.GetCurrentFrame() );
			break;
		case Tank::EOrientation::Bottom:
			pSprite_bottom->Render( position, size, rotation, depthLayer, spriteAnimator_bottom.GetCurrentFrame() );
			break;
		case Tank::EOrientation::Left:
			pSprite_left->Render( position, size, rotation, depthLayer, spriteAnimator_left.GetCurrentFrame() );
			break;
		case Tank::EOrientation::Right:
			pSprite_right->Render( position, size, rotation, depthLayer, spriteAnimator_right.GetCurrentFrame() );
			break;
		}

		if( hasShield )
		{
			// render the shield in front of the tank, but behind the trees
			pSprite_shield->Render( position, size, rotation, depthLayer + 0.1f, spriteAnimator_shield.GetCurrentFrame() );
		}
	}

	
}

void Tank::SetOrientation( EOrientation eOrientation_in )
{
	if( eOrientation == eOrientation_in )
	{
		return;
	}
	eOrientation = eOrientation_in;
	switch( eOrientation )
	{
	case Tank::EOrientation::Top:
		direction.x = 0.f;
		direction.y = 1.f;
		break;

	case Tank::EOrientation::Bottom:
		direction.x = 0.f;
		direction.y = -1.f;
		break;

	case Tank::EOrientation::Left:
		direction.x = -1.f;
		direction.y = 0.f;
		break;

	case Tank::EOrientation::Right:
		direction.x = 1.f;
		direction.y = 0.f;
		break;

	default:
		break;
	}
}

void Tank::Update( double delta )
{
	if( isSpawning )
	{
		spriteAnimator_respawn.Update( delta );
		respawnTimer.Update( delta );
	}
	else
	{
		if( hasShield )
		{
			spriteAnimator_shield.Update( delta );
			shieldTimer.Update( delta );
		}
		if( velocity > 0 )
		{
			switch( eOrientation )
			{
			case Tank::EOrientation::Top:
				spriteAnimator_top.Update( delta );
				break;
			case Tank::EOrientation::Bottom:
				spriteAnimator_bottom.Update( delta );
				break;
			case Tank::EOrientation::Left:
				spriteAnimator_left.Update( delta );
				break;
			case Tank::EOrientation::Right:
				spriteAnimator_right.Update( delta );
				break;
			}
		}
	}	
}
