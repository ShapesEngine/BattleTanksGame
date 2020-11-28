#pragma once 

#include "IGameObject.h"
#include "../../Renderer/Sprite.h"

#include <memory> 

namespace RenderEngine
{
	class Sprite;
}

class BrickWall : public IGameObject
{
public:
	BrickWall( const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, float rotation );
	inline void Render() const override { pCurrentSprite->Render( position, size, rotation ); }
	inline void Update( const uint64_t delta ) override {}

private:
	std::shared_ptr<RenderEngine::Sprite> pCurrentSprite;
};