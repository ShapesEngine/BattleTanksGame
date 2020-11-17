#pragma once

#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class AnimatedSprite;
}

class Tank
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
	Tank( std::shared_ptr<Renderer::AnimatedSprite> pSprite, float velocity, glm::vec2& position );

	void Render() const;
	void SetOrientation( EOrientation eOrientation_in );
	void Move( bool move );
	void Update( uint64_t delta );

private:
	EOrientation eOrientation = EOrientation::Top;
	std::shared_ptr<Renderer::AnimatedSprite> pSprite;
	bool move = false;
	float velocity;
	glm::vec2 position;
	glm::vec2 moveOffset = glm::vec2( 0.f, 1.f );
};