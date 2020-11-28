#include "IGameObject.h"

IGameObject::IGameObject( const glm::vec2& position, const glm::vec2& size, float rotation ) :
	position( position ),
	size( size ),
	rotation( rotation )
{}
