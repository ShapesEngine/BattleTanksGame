#pragma once

#include <memory>
#include <unordered_set>

class IGameObject;

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