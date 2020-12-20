#pragma once 

#include "IGameObject.h" 
#include "../../Renderer/SpriteAnimator.h" 
#include "../../System/Timer.h" 

#include <array> 
#include <memory> 

namespace RenderEngine
{
	class Sprite;
}

class Bullet : public IGameObject
{
public:
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

	Bullet( float velocity, const glm::vec2& position, const glm::vec2& size, const glm::vec2& explosionSize, float depthLayer );
	void Render() const override;
	void Fire( const glm::vec2& position_in, const glm::vec2& direction_in );
	void Update( double delta ) override;

	inline bool IsActive() const { return isActive; }

private:
	glm::vec2 explosionSize;
	glm::vec2 explosionOffset;
	std::shared_ptr<RenderEngine::Sprite> pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> pSprite_right;
	std::shared_ptr<RenderEngine::Sprite> pSprite_explosion;
	RenderEngine::SpriteAnimator spriteAnimator_explosion;
	Timer explosionTimer;
	EOrientation eOrientation = EOrientation::Top;
	float maxVelocity;
	bool isActive = false;
	bool isExplosion = false;
};
