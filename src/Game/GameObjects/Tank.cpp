#include "Tank.h"
#include "../../Renderer/AnimatedSprite.h"

Tank::Tank( std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, float velocity, const glm::vec2& position, const glm::vec2& size ) :
	IGameObject( position, size, 0.f ),
	pSprite( std::move( pSprite ) ),
	velocity( velocity )
{}

void Tank::Render() const
{
	pSprite->Render( position, size, rotation );
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
		pSprite->SetAnimation( "tankTopState" );
		moveOffset.x = 0.f;
		moveOffset.y = 1.f;
		break;

	case Tank::EOrientation::Bottom:
		pSprite->SetAnimation( "tankBottomState" );
		moveOffset.x = 0.f;
		moveOffset.y = -1.f;
		break;

	case Tank::EOrientation::Left:
		pSprite->SetAnimation( "tankLeftState" );
		moveOffset.x = -1.f;
		moveOffset.y = 0.f;
		break;

	case Tank::EOrientation::Right:
		pSprite->SetAnimation( "tankRightState" );
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
		pSprite->Update( delta );
	}
}
