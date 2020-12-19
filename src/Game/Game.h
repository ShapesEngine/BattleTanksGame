#pragma once

#include <glm/vec2.hpp>
#include <bitset>
#include <memory>

#include "GameObjects/Tank.h"
#include "GameObjects/Bullet.h"
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
	void Update( double delta );
	void SetKey( int key, int action );
	bool Init();

	inline size_t GetCurrentLevelWidth() const { return pLevel->GetWidth();}
	inline size_t GetCurrentLevelHeight() const { return pLevel->GetHeight(); }

private:
	std::bitset<350> keys;

	glm::ivec2 windowSize;
	EGameState eCurrentGameState = EGameState::Active;
	std::shared_ptr<Tank> pTank;
	std::shared_ptr<Level> pLevel; 
};