#pragma once

#include <memory>
#include <unordered_set>
#include <vector>
#include <functional>

#include <glm/vec2.hpp>

class IGameObject;
class Level;

namespace Physics
{
	enum class ECollisionDirection : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

	struct AABB
	{
		AABB( const glm::vec2& bottomLeft_in, const glm::vec2& topRight_in )
			: bottomLeft( bottomLeft_in )
			, topRight( topRight_in )
		{}
		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};

	struct Collider
	{
		using clCallbackFn = std::function<void( const IGameObject*, const ECollisionDirection )>;

		Collider( const glm::vec2& bottomLeft, const glm::vec2& topRight, clCallbackFn onCollisionCallback = {} ) :
			boundingBox( bottomLeft, topRight ),
			onCollisionCallback( onCollisionCallback )
		{}

		Collider( const AABB& boundingBox, clCallbackFn onCollisionCallback = {} ) : 
			boundingBox( boundingBox ),
			onCollisionCallback( onCollisionCallback )
		{}

		AABB boundingBox;
		bool isActive = true;
		clCallbackFn onCollisionCallback;
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
		static bool HasIntersection( const Collider& collider1, const glm::vec2& position1,
									 const Collider& collider2, const glm::vec2& position2 );

	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> dynamicObjects;
		static std::shared_ptr<Level> pCurrentLevel;		
	};
}