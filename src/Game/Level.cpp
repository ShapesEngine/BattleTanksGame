#include "Level.h" 

#include "GameObjects/BrickWall.h" 
#include "GameObjects/ConcreteWall.h" 
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"

#include <iostream>
#include <algorithm>
#include <cmath>

Level::Level( const std::vector<std::string>& levelDescription )
{
	if( levelDescription.empty() )
	{
		std::cerr << "Empty level description!" << std::endl;
	}

	widthBlocks = levelDescription[0].length();
	heightBlocks = levelDescription.size();
	widthPixels = uint32_t( widthBlocks * BLOCK_SIZE );
	heightPixels = uint32_t( heightBlocks * BLOCK_SIZE );

	levelObjects.reserve( widthBlocks * heightBlocks + 4 );
	constexpr float HALF_BLOCK_SIZE = BLOCK_SIZE / 2.f;
	// offset is needed because of the fact that positions are loaded from bottom to top,
	// while level is loaded from top to bottom
	uint32_t currentBottomOffset = uint32_t( BLOCK_SIZE * ( heightBlocks - 1 ) + HALF_BLOCK_SIZE );
	/* default respawn positions */
	playerRespawn_1Pos = { BLOCK_SIZE * ( widthBlocks / 2 - 1 ), BLOCK_SIZE / 2 };
	playerRespawn_2Pos = { BLOCK_SIZE * ( widthBlocks / 2 + 3 ), BLOCK_SIZE / 2 };
	enemyRespawn_1Pos = { BLOCK_SIZE, BLOCK_SIZE * heightBlocks - BLOCK_SIZE / 2 };
	enemyRespawn_2Pos = { BLOCK_SIZE * ( widthBlocks / 2 + 1 ), BLOCK_SIZE * heightBlocks - BLOCK_SIZE / 2 };
	enemyRespawn_3Pos = { BLOCK_SIZE * widthBlocks, BLOCK_SIZE * heightBlocks - BLOCK_SIZE / 2 };
	for( const std::string& currentRow : levelDescription )
	{
		uint32_t currentLeftOffset = BLOCK_SIZE;
		for( const char currentElement : currentRow )
		{
			switch( currentElement )
			{
			case 'K':
				playerRespawn_1Pos = { currentLeftOffset, currentBottomOffset };
				levelObjects.emplace_back( nullptr );
				break;
			case 'L':
				playerRespawn_2Pos = { currentLeftOffset, currentBottomOffset };
				levelObjects.emplace_back( nullptr );
				break;
			case 'M':
				enemyRespawn_1Pos = { currentLeftOffset, currentBottomOffset };
				levelObjects.emplace_back( nullptr );
				break;
			case 'N':
				enemyRespawn_2Pos = { currentLeftOffset, currentBottomOffset };
				levelObjects.emplace_back( nullptr );
				break;
			case 'O':
				enemyRespawn_3Pos = { currentLeftOffset, currentBottomOffset };
				levelObjects.emplace_back( nullptr );
				break;
			default:
				levelObjects.emplace_back( CreateGameObjectFromDescription( currentElement, glm::vec2( currentLeftOffset, currentBottomOffset ), glm::vec2( BLOCK_SIZE, BLOCK_SIZE ), 0.f ) );
				break;
			}
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	// =======================================================================
	// Borders
	// -----------------------------------------------------------------------
	// BOTTOM
	levelObjects.emplace_back( std::make_shared<Border>( glm::vec2( BLOCK_SIZE, 0.f ), glm::vec2( widthBlocks * BLOCK_SIZE, HALF_BLOCK_SIZE ), 0.f ) );
	// TOP
	levelObjects.emplace_back( std::make_shared<Border>( glm::vec2( BLOCK_SIZE, heightBlocks * BLOCK_SIZE + HALF_BLOCK_SIZE ), glm::vec2( widthBlocks * BLOCK_SIZE, HALF_BLOCK_SIZE ), 0.f ) );
	// LEFT
	levelObjects.emplace_back( std::make_shared<Border>( glm::vec2( 0.f, 0.f ), glm::vec2( BLOCK_SIZE, ( heightBlocks + 1 ) * BLOCK_SIZE ), 0.f ) );
	// RIGHT
	levelObjects.emplace_back( std::make_shared<Border>( glm::vec2( ( widthBlocks + 1 ) * BLOCK_SIZE, 0.f ), glm::vec2( BLOCK_SIZE * 2.f, ( heightBlocks + 1 ) * BLOCK_SIZE ), 0.f ) );
}

void Level::Render() const
{
	for( const auto& currentLevelObject : levelObjects )
	{
		if( currentLevelObject )
		{
			currentLevelObject->Render();
		}
	}
}

void Level::Update( double delta )
{
	for( const auto& currentLevelObject : levelObjects )
	{
		if( currentLevelObject )
		{
			currentLevelObject->Update( delta );
		}
	}
}

std::vector<std::shared_ptr<IGameObject>> Level::GetObjectsInArea( const glm::vec2& bottomLeft, const glm::vec2& topRight ) const
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve( 9 );

	glm::vec2 bottomLeft_converted( std::clamp( bottomLeft.x - BLOCK_SIZE, 0.f, (float)widthPixels ),
									std::clamp( heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, (float)heightPixels ) );
	glm::vec2 topRight_converted( std::clamp( topRight.x - BLOCK_SIZE, 0.f, (float)widthPixels ),
								  std::clamp( heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, (float)heightPixels ) );

	size_t startX = size_t( floor( bottomLeft_converted.x / BLOCK_SIZE ) );
	size_t endX = size_t( ceil( topRight_converted.x / BLOCK_SIZE ) );

	size_t startY = size_t( floor( topRight_converted.y / BLOCK_SIZE ) );
	size_t endY = size_t( ceil( bottomLeft_converted.y / BLOCK_SIZE ) );

	for( size_t currentColumn = startX; currentColumn < endX; ++currentColumn )
	{
		for( size_t currentRow = startY; currentRow < endY; ++currentRow )
		{
			auto& currentObject = levelObjects[currentRow * widthBlocks + currentColumn];
			if( currentObject )
			{
				output.push_back( currentObject );
			}
		}
	}

	if( endX >= widthBlocks )
	{
		output.push_back( levelObjects[levelObjects.size() - 1] );
	}
	if( startX <= 1 )
	{
		output.push_back( levelObjects[levelObjects.size() - 2] );
	}
	if( startY <= 1 )
	{
		output.push_back( levelObjects[levelObjects.size() - 3] );
	}
	if( endY >= heightBlocks )
	{
		output.push_back( levelObjects[levelObjects.size() - 4] );
	}

	return output;
}

std::shared_ptr<IGameObject> Level::CreateGameObjectFromDescription( char description, const glm::vec2& position, const glm::vec2& size, float rotation )
{
	switch( description )
	{
	case '0':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::Right, position, size, rotation );
	case '1':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::Bottom, position, size, rotation );
	case '2':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::Left, position, size, rotation );
	case '3':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::Top, position, size, rotation );
	case '4':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::All, position, size, rotation );
	case 'G':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::BottomLeft, position, size, rotation );
	case 'H':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::BottomRight, position, size, rotation );
	case 'I':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::TopLeft, position, size, rotation );
	case 'J':
		return std::make_shared<BrickWall>( BrickWall::EBrickWallType::TopRight, position, size, rotation );
	case '5':
		return std::make_shared<ConcreteWall>( ConcreteWall::EConcreteWallType::Right, position, size, rotation );
	case '6':
		return std::make_shared<ConcreteWall>( ConcreteWall::EConcreteWallType::Bottom, position, size, rotation );
	case '7':
		return std::make_shared<ConcreteWall>( ConcreteWall::EConcreteWallType::Left, position, size, rotation );
	case '8':
		return std::make_shared<ConcreteWall>( ConcreteWall::EConcreteWallType::Top, position, size, rotation );
	case '9':
		return std::make_shared<ConcreteWall>( ConcreteWall::EConcreteWallType::All, position, size, rotation );
	case 'A':
		return std::make_shared<Water>( position, size, rotation );
	case 'B':
		return std::make_shared<Trees>( position, size, rotation, 1.f );
	case 'C':
		return std::make_shared<Ice>( position, size, rotation, -1.f );
	case 'E':
		return std::make_shared<Eagle>( position, size, rotation );
	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;
		[[fallthrough]];
	case 'D':
		return nullptr;
	}
}