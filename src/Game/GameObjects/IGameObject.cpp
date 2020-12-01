#include "IGameObject.h"

IGameObject::IGameObject( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer ) :
	position( position ),
	size( size ),
	rotation( rotation ),
	depthLayer( depthLayer )
{}
