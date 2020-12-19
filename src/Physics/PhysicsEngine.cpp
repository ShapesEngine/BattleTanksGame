#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"

namespace Physics
{
	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::pCurrentLevel;

	void PhysicsEngine::Update( double delta )
	{
		for( auto& currentObject : dynamicObjects )
		{
			if( currentObject->GetCurrentVelocity() > 0.f )
			{
				// align position to multiple of 4 pixels 
				if( currentObject->GetCurrentDirection().x != 0.f ) // right and left 
				{
					currentObject->SetCurrentPosition( glm::vec2( currentObject->GetCurrentPosition().x, uint32_t( currentObject->GetCurrentPosition().y / 4.f + 0.5f ) * 4.f ) );
				}
				else if( currentObject->GetCurrentDirection().y != 0.f ) // top and bottom 
				{
					currentObject->SetCurrentPosition( glm::vec2( uint32_t( currentObject->GetCurrentPosition().x / 4.f + 0.5f ) * 4.f, currentObject->GetCurrentPosition().y ) );
				}

				const auto newPosition = currentObject->GetCurrentPosition() + currentObject->GetCurrentDirection() * float( currentObject->GetCurrentVelocity() * delta );
				const auto& colliders = currentObject->GetColliders();
				std::vector<std::shared_ptr<IGameObject>> objectsToCheck = pCurrentLevel->GetObjectsInArea( newPosition, newPosition + currentObject->GetSize() );

				bool hasCollision = false;
				for( const auto& currentObjectToCheck : objectsToCheck )
				{
					const auto& collidersToCheck = currentObjectToCheck->GetColliders();
					if( !collidersToCheck.empty() )
					{
						if( HasIntersection( colliders, newPosition, collidersToCheck, currentObjectToCheck->GetCurrentPosition() ) )
						{
							hasCollision = true;
							break;
						}
					}
				}

				if( !hasCollision )
				{
					currentObject->SetCurrentPosition( newPosition );
				}
				else
				{
					// align position to multiple of 8 pixels 
					if( currentObject->GetCurrentDirection().x != 0.f ) // right and left 
					{
						currentObject->SetCurrentPosition( glm::vec2( uint32_t( currentObject->GetCurrentPosition().x / 8.f + 0.5f ) * 8.f, currentObject->GetCurrentPosition().y ) );
					}
					else if( currentObject->GetCurrentDirection().y != 0.f ) // top and bottom 
					{
						currentObject->SetCurrentPosition( glm::vec2( currentObject->GetCurrentPosition().x, uint32_t( currentObject->GetCurrentPosition().y / 8.f + 0.5f ) * 8.f ) );
					}
				}
			}
		}
	}

	void PhysicsEngine::Terminate()
	{
		dynamicObjects.clear();
		pCurrentLevel.reset();
	}

	bool PhysicsEngine::HasIntersection( const std::vector<AABB>& colliders1, const glm::vec2& position1, const std::vector<AABB>& colliders2, const glm::vec2& position2 )
	{
		for( const auto& currentCollider1 : colliders1 )
		{
			const glm::vec2 currentCollider1_bottomLeft_world = currentCollider1.bottomLeft + position1;
			const glm::vec2 currentCollider1_topRight_world = currentCollider1.topRight + position1;
			for( const auto& currentCollider2 : colliders2 )
			{
				const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottomLeft + position2;
				const glm::vec2 currentCollider2_topRight_world = currentCollider2.topRight + position2;

				if( currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x )
				{
					return false;
				}
				if( currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x )
				{
					return false;
				}

				if( currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y )
				{
					return false;
				}
				if( currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y )
				{
					return false;
				}
			}
		}

		return true;
	}
}
