#pragma once

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

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
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

public:
	Tank( float maxVelocity, const glm::vec2& position, const glm::vec2& size, float depthLayer = 0 );

	void Render() const override;
	void SetOrientation( EOrientation eOrientation_in );
	void Update( double delta ) override;

	float GetMaxVelocity() const { return maxVelocity; }
	inline void SetVelocity( float velocity_in ) override { velocity = ( isSpawning ? 0.f : velocity_in ); }

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
	std::shared_ptr<RenderEngine::Sprite> pSprite_respawn;
	RenderEngine::SpriteAnimator spriteAnimator_respawn;
	std::shared_ptr<RenderEngine::Sprite> pSprite_shield;
	RenderEngine::SpriteAnimator spriteAnimator_shield;

	Timer respawnTimer;
	Timer shieldTimer;
	
	float maxVelocity;
	bool isSpawning = true;
	bool hasShield = false;
};