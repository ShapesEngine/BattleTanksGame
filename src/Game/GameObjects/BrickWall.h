#pragma once 

#include "IGameObject.h"
#include "../../Renderer/Sprite.h"

#include <memory> 
#include <array>

namespace RenderEngine
{
	class Sprite;
}

class BrickWall : public IGameObject
{
public:
	enum class EBrickWallType
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

	enum class EBrickState
	{
		All = 0,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};

	enum class EBrickLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

public:
	BrickWall( EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer = 0 );
	inline void Render() const override;
	inline void Update( double delta ) override {};

private:
	void RenderBrick( const EBrickLocation eBrickLocation ) const;

	std::array<EBrickState, 4> eCurrentBrickState;
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> sprites;
	std::array<glm::vec2, 4> blockOffsets; 
};