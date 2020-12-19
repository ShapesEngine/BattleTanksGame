#pragma once 

#include <glm/vec2.hpp> 

#include "../../Physics/PhysicsEngine.h"

class IGameObject
{
public:
	IGameObject( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer );
	virtual ~IGameObject() = default;

	virtual void Render() const = 0;
	virtual void Update( double delta ) = 0;	
	virtual void OnCollision() {};

	inline const glm::vec2& GetCurrentPosition() const { return position; }
	inline void SetCurrentPosition( const glm::vec2& position_in ) { position = position_in; }
	inline const glm::vec2& GetCurrentDirection() const { return direction; }
	inline const float GetCurrentVelocity() const { return velocity; }
	inline virtual void SetVelocity( float velocity_in ) { velocity = velocity_in; }
	inline virtual bool IsCollidableWithSecondObject( IGameObject* obj = nullptr ) const { return collidable; }

	const glm::vec2& GetSize() const { return size; }
	const std::vector<Physics::AABB>& GetColliders() const { return colliders; }

protected:
	glm::vec2 position;
	glm::vec2 direction = glm::vec2( 0.f, 1.f );
	glm::vec2 size;
	float rotation;
	float depthLayer;
	float velocity = 0.f;
	bool collidable = true;
	std::vector<Physics::AABB> colliders; 
};