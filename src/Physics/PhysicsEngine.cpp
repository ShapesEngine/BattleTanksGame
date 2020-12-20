#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"
#include "../Game/GameObjects/Water.h"

namespace Physics
{
	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::pCurrentLevel;

	void PhysicsEngine::Update( double delta )
	{
		for( auto& currentDynamicObject : dynamicObjects )
		{
			if( currentDynamicObject->GetCurrentVelocity() > 0.f )
			{
				// align position to multiple of 4 pixels 
				if( currentDynamicObject->GetCurrentDirection().x != 0.f ) // right and left 
				{
					currentDynamicObject->SetCurrentPosition( glm::vec2( currentDynamicObject->GetCurrentPosition().x, uint32_t( currentDynamicObject->GetCurrentPosition().y / 4.f + 0.5f ) * 4.f ) );
				}
				else if( currentDynamicObject->GetCurrentDirection().y != 0.f ) // top and bottom 
				{
					currentDynamicObject->SetCurrentPosition( glm::vec2( uint32_t( currentDynamicObject->GetCurrentPosition().x / 4.f + 0.5f ) * 4.f, currentDynamicObject->GetCurrentPosition().y ) );
				}

				const auto newPosition = currentDynamicObject->GetCurrentPosition() + currentDynamicObject->GetCurrentDirection() * float( currentDynamicObject->GetCurrentVelocity() * delta );
				std::vector<std::shared_ptr<IGameObject>> objectsToCheck = pCurrentLevel->GetObjectsInArea( newPosition, newPosition + currentDynamicObject->GetSize() );

				const auto& colliders = currentDynamicObject->GetColliders();
				bool hasCollision = false;
				ECollisionDirection dynamicObjectCollisionDirection = ECollisionDirection::Right;
				if( currentDynamicObject->GetCurrentDirection().x < 0.f ) 
					dynamicObjectCollisionDirection = ECollisionDirection::Left;
				else if( currentDynamicObject->GetCurrentDirection().y > 0.f ) 
					dynamicObjectCollisionDirection = ECollisionDirection::Top;
				else if( currentDynamicObject->GetCurrentDirection().y < 0.f ) 
					dynamicObjectCollisionDirection = ECollisionDirection::Bottom;

				ECollisionDirection objectCollisionDirection = ECollisionDirection::Left;
				if( currentDynamicObject->GetCurrentDirection().x < 0.f ) 
					objectCollisionDirection = ECollisionDirection::Right;
				else if( currentDynamicObject->GetCurrentDirection().y > 0.f ) 
					objectCollisionDirection = ECollisionDirection::Bottom;
				else if( currentDynamicObject->GetCurrentDirection().y < 0.f ) 
					objectCollisionDirection = ECollisionDirection::Top;

				for( const auto& currentDynamicObjectCollider : colliders )
				{
					for( const auto& currentObjectToCheck : objectsToCheck )
					{
						const auto& collidersToCheck = currentObjectToCheck->GetColliders();
						if( currentObjectToCheck->IsCollidableWithSecondObject( currentDynamicObject.get() ) && !collidersToCheck.empty() )
						{
							for( const auto& currentObjectCollider : currentObjectToCheck->GetColliders() )
							{
								if( currentObjectCollider.isActive && HasIntersection( currentDynamicObjectCollider, newPosition, currentObjectCollider, currentObjectToCheck->GetCurrentPosition() ) )
								{
									hasCollision = true;
									if( currentObjectCollider.onCollisionCallback )
									{
										currentObjectCollider.onCollisionCallback( currentDynamicObject.get(), objectCollisionDirection );
									}
									if( currentDynamicObjectCollider.onCollisionCallback )
									{
										currentDynamicObjectCollider.onCollisionCallback( currentObjectToCheck.get(), dynamicObjectCollisionDirection );
									}
								}
							}
						}
					}
				}

				if( !hasCollision )
				{
					currentDynamicObject->SetCurrentPosition( newPosition );
				}
				else
				{
					// align position to multiple of 8 pixels 
					if( currentDynamicObject->GetCurrentDirection().x != 0.f ) // right and left 
					{
						currentDynamicObject->SetCurrentPosition( glm::vec2( uint32_t( currentDynamicObject->GetCurrentPosition().x / 4.f + 0.5f ) * 4.f, currentDynamicObject->GetCurrentPosition().y ) );
					}
					else if( currentDynamicObject->GetCurrentDirection().y != 0.f ) // top and bottom 
					{
						currentDynamicObject->SetCurrentPosition( glm::vec2( currentDynamicObject->GetCurrentPosition().x, uint32_t( currentDynamicObject->GetCurrentPosition().y / 4.f + 0.5f ) * 4.f ) );
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

	bool PhysicsEngine::HasIntersection( const Collider& collider1, const glm::vec2& position1,
										 const Collider& collider2, const glm::vec2& position2 )
	{
		const glm::vec2 collider1_bottomLeft_world = collider1.boundingBox.bottomLeft + position1;
		const glm::vec2 collider1_topRight_world = collider1.boundingBox.topRight + position1;

		const glm::vec2 collider2_bottomLeft_world = collider2.boundingBox.bottomLeft + position2;
		const glm::vec2 collider2_topRight_world = collider2.boundingBox.topRight + position2;

		if( collider1_bottomLeft_world.x >= collider2_topRight_world.x )
		{
			return false;
		}
		if( collider1_topRight_world.x <= collider2_bottomLeft_world.x )
		{
			return false;
		}

		if( collider1_bottomLeft_world.y >= collider2_topRight_world.y )
		{
			return false;
		}
		if( collider1_topRight_world.y <= collider2_bottomLeft_world.y )
		{
			return false;
		}

		return true;
	}
}
