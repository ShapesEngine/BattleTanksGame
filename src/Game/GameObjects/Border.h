#pragma once 

#include "IGameObject.h"
#include "../../Renderer/Sprite.h"

#include <memory> 

namespace RenderEngine
{
	class Sprite;
}

class Border : public IGameObject
{
public:
	Border( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer = 0 );
	inline void Render() const override;
	inline void Update( double delta ) override {};

private:
	std::shared_ptr<RenderEngine::Sprite> pSprite;
};