#include "Tank.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Tank::Tank(	float velocity, const glm::vec2& position, const glm::vec2& size ) :
	IGameObject( position, size, 0.f ),
	pSprite_top( ResourceManager::GetSprite( "TankSprite_Top" ) ),
	pSprite_bottom( ResourceManager::GetSprite( "TankSprite_Bottom" ) ),
	pSprite_left( ResourceManager::GetSprite( "TankSprite_Left" )),
	pSprite_right( ResourceManager::GetSprite( "TankSprite_Right" ) ),
	spriteAnimator_top( pSprite_top ),
	spriteAnimator_bottom( pSprite_bottom ),
	spriteAnimator_left( pSprite_left ),
	spriteAnimator_right( pSprite_right ),
	velocity( velocity )
{}

void Tank::Render() const
{
	switch( eOrientation )
	{
	case Tank::EOrientation::Top:
		pSprite_top->Render( position, size, rotation, spriteAnimator_top.GetCurrentFrame() );
		break;
	case Tank::EOrientation::Bottom:
		pSprite_bottom->Render( position, size, rotation, spriteAnimator_bottom.GetCurrentFrame() );
		break;
	case Tank::EOrientation::Left:
		pSprite_left->Render( position, size, rotation, spriteAnimator_left.GetCurrentFrame() );
		break;
	case Tank::EOrientation::Right:
		pSprite_right->Render( position, size, rotation, spriteAnimator_right.GetCurrentFrame() );
		break;
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
		moveOffset.x = 0.f;
		moveOffset.y = 1.f;
		break;

	case Tank::EOrientation::Bottom:
		moveOffset.x = 0.f;
		moveOffset.y = -1.f;
		break;

	case Tank::EOrientation::Left:
		moveOffset.x = -1.f;
		moveOffset.y = 0.f;
		break;

	case Tank::EOrientation::Right:
		moveOffset.x = 1.f;
		moveOffset.y = 0.f;
		break;

	default:
		break;
	}
}

void Tank::Update( uint64_t delta )
{
	if( move )
	{
		position += delta * velocity * moveOffset;
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
