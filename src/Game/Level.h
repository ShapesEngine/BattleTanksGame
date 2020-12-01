#pragma once 

#include <vector> 
#include <string> 
#include <memory> 

#include <glm/vec2.hpp>

class IGameObject;

class Level
{
public:
	Level( const std::vector<std::string>& levelDescription );
	void Render() const;
	void Update( uint64_t delta );

	inline size_t GetWidth() const { return( width + 3 ) * BLOCK_SIZE; }
	inline size_t GetHeight() const { return( height + 1 ) * BLOCK_SIZE; }

private:
	std::shared_ptr<IGameObject> CreateGameObjectFromDescription( char description, const glm::vec2& position, const glm::vec2& size, float rotation );

private:
	size_t width = 0;
	size_t height = 0;

	static constexpr uint32_t BLOCK_SIZE = 16u;

	std::vector<std::shared_ptr<IGameObject>> levelObjects;
};