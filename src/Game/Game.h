#pragma once

#include <glm/vec2.hpp>
#include <bitset>

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
	// 256 possible ANSI keys that might be pressed
	std::bitset<256> keys;

	glm::ivec2 windowSize;
	EGameState eCurrentGameState = EGameState::Active;
};