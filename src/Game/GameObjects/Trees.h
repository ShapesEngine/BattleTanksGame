#pragma once 

#include "IGameObject.h"
#include "../../Renderer/Sprite.h"

#include <memory> 
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class Trees : public IGameObject
{
public:
	enum class EBlockLocation : uint8_t
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

public:
	Trees( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer = 0 );
	inline void Render() const override;
	inline void Update( double delta ) override {};

private:
	void RenderBrick( const EBlockLocation eBlockLocation ) const;

private:
	std::shared_ptr<RenderEngine::Sprite> pSprite;
	std::array<glm::vec2, 4> blockOffsets; 
};