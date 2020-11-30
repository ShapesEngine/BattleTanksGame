#pragma once

#include <glm/vec2.hpp>
#include <bitset>
#include <memory>

#include "GameObjects/Tank.h"
#include "Level.h"

class Level;

class Game
{
public:
	enum class EGameState
	{
		Active,
		Pause
	};

public:
	Game( const glm::ivec2& windowSize );

	void Render();
	void Update( uint64_t delta );
	void SetKey( int key, int action );
	bool Init();

private:
	std::bitset<350> keys;

	glm::ivec2 windowSize;
	EGameState eCurrentGameState = EGameState::Active;
	std::unique_ptr<Tank> pTank;
	std::unique_ptr<Level> pLevel; 
};