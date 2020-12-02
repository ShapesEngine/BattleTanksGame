#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"

std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::pDynamicObjects;

void PhysicsEngine::Update( double delta )
{
	for( auto& currentObject : pDynamicObjects )
	{
		if( currentObject->GetCurrentVelocity() > 0 )
		{
			currentObject->SetCurrentPosition( currentObject->GetCurrentPosition() + currentObject->GetCurrentDirection() * float( currentObject->GetCurrentVelocity() * delta ) );
		}
	}
}
