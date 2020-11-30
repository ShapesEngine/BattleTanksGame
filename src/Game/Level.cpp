#include "Level.h" 

#include "GameObjects/BrickWall.h" 
#include "GameObjects/ConcreteWall.h" 

#include <iostream>

Level::Level( const std::vector<std::string>& levelDescription )
{
	if( levelDescription.empty() )
	{
		std::cerr << "Empty level description!" << std::endl;
	}

	width = levelDescription[0].length();
	height = levelDescription.size();

	levelObjects.reserve( width * height );
	// offset is needed because of the fact that positions are loaded from bottom to top,
	// while level is loaded from top to bottom
	uint32_t currentBottomOffset = static_cast<uint32_t>( BLOCK_SIZE * ( height - 1 ) );
	for( const std::string& currentRow : levelDescription )
	{
		uint32_t currentLeftOffset = 0;
		for( const char currentElement : currentRow )
		{
			levelObjects.emplace_back( CreateGameObjectFromDescription( currentElement, glm::vec2( currentLeftOffset, currentBottomOffset ), glm::vec2( BLOCK_SIZE, BLOCK_SIZE ), 0.f ) );
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
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

void Level::Update( const uint64_t delta )
{
	for( const auto& currentLevelObject : levelObjects )
	{
		if( currentLevelObject )
		{
			currentLevelObject->Update( delta );
		}
	}
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
	case 'D':
		return nullptr;
	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;
		return nullptr;
	}
}