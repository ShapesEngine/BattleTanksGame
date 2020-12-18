#pragma once

#include <memory>
#include <unordered_set>

#include <glm/vec2.hpp>

class IGameObject;
class Level;

namespace Physics
{
	struct AABB
	{
		AABB( const glm::vec2& bottomLeft_in, const glm::vec2& topRight_in )
			: bottomLeft( bottomLeft_in )
			, topRight( topRight_in )
		{}
		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};

	class PhysicsEngine
	{
	public:
		PhysicsEngine() = delete;
		PhysicsEngine( const PhysicsEngine& ) = delete;
		PhysicsEngine( PhysicsEngine&& ) = delete;
		PhysicsEngine operator=( const PhysicsEngine& ) = delete;
		PhysicsEngine operator=( PhysicsEngine&& ) = delete;
		~PhysicsEngine() = delete;

		static void Init() {}
		static void Update( double delta );

		inline static void Terminate() { pDynamicObjects.clear(); }
		inline static void AddDynamicGameObject( std::shared_ptr<IGameObject> pGameObject ) { pDynamicObjects.insert( std::move( pGameObject ) ); }

	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> pDynamicObjects;
	};
}