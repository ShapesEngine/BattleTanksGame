#pragma once 

#include "IGameObject.h"

#include <memory> 
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class Eagle : public IGameObject
{
public:
	enum class EEagleState : uint8_t
	{
		Alive = 0,
		Dead,
	};

public:
	Eagle( const glm::vec2& position, const glm::vec2& size, float rotation );
	inline void Render() const override;
	inline void Update( const uint64_t delta ) override { };

private:
	std::array<std::shared_ptr<RenderEngine::Sprite>, 2> pSprites;
	EEagleState eCurrentState; 
};