#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

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
		static void Terminate();

		inline static void SetCurrentLevel( std::shared_ptr<Level> pLevel ) { pCurrentLevel.swap( pLevel ); }		
		inline static void AddDynamicGameObject( std::shared_ptr<IGameObject> pGameObject ) { dynamicObjects.insert( std::move( pGameObject ) ); }

	private:
		static bool HasIntersection( const std::vector<AABB>& colliders1, const glm::vec2& position1,
									 const std::vector<AABB>& colliders2, const glm::vec2& position2 );

	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> dynamicObjects;
		static std::shared_ptr<Level> pCurrentLevel;		
	};
}