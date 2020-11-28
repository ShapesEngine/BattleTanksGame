#pragma once 

#include <vector> 
#include <string> 
#include <memory> 

class IGameObject;

class Level
{
public:
	Level( const std::vector<std::string>& levelDescription );
	void Render() const;
	void Update( uint64_t delta );

private:
	size_t width = 0;
	size_t height = 0;

	std::vector<std::shared_ptr<IGameObject>> levelObjects;
};