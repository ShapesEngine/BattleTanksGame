#pragma once

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

#include <memory>

#include <glm/vec2.hpp>

namespace RenderEngine
{
	class Sprite;
	class SpriteAnimator;
}

class Tank : public IGameObject
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};

public:
	Tank( float velocity, const glm::vec2& position, const glm::vec2& size );

	void Render() const override;
	void SetOrientation( EOrientation eOrientation_in );
	void Update( uint64_t delta ) override;

	inline void Move( bool move ) { this->move = move; }

private:
	EOrientation eOrientation = EOrientation::Top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> pSprite_right;
	RenderEngine::SpriteAnimator spriteAnimator_top;
	RenderEngine::SpriteAnimator spriteAnimator_bottom;
	RenderEngine::SpriteAnimator spriteAnimator_left;
	RenderEngine::SpriteAnimator spriteAnimator_right;
	bool move = false;
	float velocity;
	glm::vec2 moveOffset = glm::vec2( 0.f, 1.f );
};