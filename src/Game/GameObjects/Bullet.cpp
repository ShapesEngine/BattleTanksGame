#include "Bullet.h"
#include "../../Resources/ResourceManager.h" 
#include "../../Renderer/Sprite.h"

Bullet::Bullet( float velocity, const glm::vec2& position, const glm::vec2& size, const glm::vec2& explosionSize, float depthLayer ) : 
	IGameObject( position, size, 0.f, depthLayer ),
	explosionSize( explosionSize ),
	explosionOffset( ( explosionSize - size ) / 2.f ),
	pSprite_top( ResourceManager::GetSprite( "bullet_top" ) ),
	pSprite_bottom( ResourceManager::GetSprite( "bullet_bottom" ) ),
	pSprite_left( ResourceManager::GetSprite( "bullet_left" ) ),
	pSprite_right( ResourceManager::GetSprite( "bullet_right" ) ),
	pSprite_explosion( ResourceManager::GetSprite( "explosion" ) ),
	spriteAnimator_explosion( pSprite_explosion ),
	maxVelocity( velocity )
{
	colliders.emplace_back( glm::vec2( 0 ), size );
	explosionTimer.SetCallback( [&]() { isExplosion = isActive = false;	} );
}

void Bullet::Render() const
{
	if( isExplosion )
	{
		switch( auto currentFrame = spriteAnimator_explosion.GetCurrentFrame(); eOrientation )
		{
		case EOrientation::Top:
			pSprite_explosion->Render( position - explosionOffset + glm::vec2( 0.f, size.y / 2.f ), explosionSize, rotation, depthLayer + 0.1f, currentFrame );
			break;
		case EOrientation::Bottom:
			pSprite_explosion->Render( position - explosionOffset - glm::vec2( 0.f, size.y / 2.f ), explosionSize, rotation, depthLayer + 0.1f, currentFrame );
			break;
		case EOrientation::Left:
			pSprite_explosion->Render( position - explosionOffset - glm::vec2( size.x / 2.f, 0.f ), explosionSize, rotation, depthLayer + 0.1f, currentFrame );
			break;
		case EOrientation::Right:
			pSprite_explosion->Render( position - explosionOffset + glm::vec2( size.x / 2.f, 0.f ), explosionSize, rotation, depthLayer + 0.1f, currentFrame );
			break;
		}
	}
	else
	{
		switch( eOrientation )
		{
		case EOrientation::Top:
			pSprite_top->Render( position, size, rotation, depthLayer );
			break;
		case EOrientation::Bottom:
			pSprite_bottom->Render( position, size, rotation, depthLayer );
			break;
		case EOrientation::Left:
			pSprite_left->Render( position, size, rotation, depthLayer );
			break;
		case EOrientation::Right:
			pSprite_right->Render( position, size, rotation, depthLayer );
			break;
		}
	}
}

void Bullet::Fire( const glm::vec2 & position_in, const glm::vec2 & direction_in )
{
	position = position_in;
	direction = direction_in;
	if( direction.x == 0.f )
	{
		eOrientation = ( direction.y < 0 ) ? EOrientation::Bottom : EOrientation::Top;
	}
	else
	{
		eOrientation = ( direction.x < 0 ) ? EOrientation::Left : EOrientation::Right;
	}
	isActive = true;
	SetVelocity( maxVelocity );
}

void Bullet::OnCollision()
{
	SetVelocity( 0.f );
	isExplosion = true;
	spriteAnimator_explosion.Reset();
	explosionTimer.Start( spriteAnimator_explosion.GetTotalDuration() );
}

void Bullet::Update( double delta )
{
	if( isExplosion )
	{
		spriteAnimator_explosion.Update( delta );
		explosionTimer.Update( delta );
	}
}
