#pragma once 

#include "IGameObject.h"
#include "../../Renderer/Sprite.h"

#include <memory> 
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class ConcreteWall : public IGameObject
{
public:
	enum class EConcreteWallType
	{
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	enum class EConcreteState
	{
		Enabled = 0,
		Destroyed
	};

	enum class EConcreteLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

public:
	ConcreteWall( EConcreteWallType eConcreteWallType, const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer = 0 );
	inline void Render() const override;
	inline void Update( const uint64_t delta ) override {};

private:
	void RenderBrick( const EConcreteLocation eBlockLocation ) const;

private:
	std::array<EConcreteState, 4> eCurrentBlockState;
	std::shared_ptr<RenderEngine::Sprite> pSprite;
	std::array<glm::vec2, 4> blockOffsets; 
};