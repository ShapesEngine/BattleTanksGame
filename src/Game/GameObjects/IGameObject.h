#pragma once 

#include <glm/vec2.hpp> 

class IGameObject
{
public:
	IGameObject( const glm::vec2& position, const glm::vec2& size, float rotation );
	virtual ~IGameObject() = default;

	virtual void Render() const = 0;
	virtual void Update( const uint64_t delta ) = 0;	

protected:
	glm::vec2 position;
	glm::vec2 size;
	float rotation;
};