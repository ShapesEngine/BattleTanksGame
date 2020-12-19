#pragma once 

#include "IGameObject.h" 

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

	Bullet( float velocity, const glm::vec2& position, const glm::vec2& size, float depthLayer );
	void Render() const override;
	void Fire( const glm::vec2& position_in, const glm::vec2& direction_in );
	void Update( double delta ) override {};

	inline bool IsActive() const { return isActive; }

private:
	std::shared_ptr<RenderEngine::Sprite> pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> pSprite_right;
	EOrientation eOrientation = EOrientation::Top;
	bool isActive = false;
};
