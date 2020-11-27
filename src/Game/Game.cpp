#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Renderer/Renderer.h"
#include "../Resources/ResourceManager.h"
#include "../Utils/ShaderHelper.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game( const glm::ivec2& windowSize ) :
    windowSize( windowSize )
{}

void Game::Render()
{
    ResourceManager::GetAnimatedSprite("NewAnimatedSprite")->Render();
	if( pTank )
	{
		pTank->Render();
	}
}

void Game::Update( uint64_t delta )
{
    ResourceManager::GetAnimatedSprite("NewAnimatedSprite")->Update(delta);

	if( pTank )
	{
		if( keys[GLFW_KEY_W] )
		{
			pTank->SetOrientation( Tank::EOrientation::Top );
			pTank->Move( true );
		}
		else if( keys[GLFW_KEY_A] )
		{
			pTank->SetOrientation( Tank::EOrientation::Left );
			pTank->Move( true );
		}
		else if( keys[GLFW_KEY_D] )
		{
			pTank->SetOrientation( Tank::EOrientation::Right );
			pTank->Move( true );
		}
		else if( keys[GLFW_KEY_S] )
		{
			pTank->SetOrientation( Tank::EOrientation::Bottom );
			pTank->Move( true );
		}
		else
		{
			pTank->Move( false );
		}

		pTank->Update( delta );
	}
}

void Game::SetKey( int key, int action )
{
    keys[key] = action;	
}

bool Game::Init()
{
	ResourceManager::loadJSONResources( "res/resources.json" );
	auto pSpriteShaderProgram = ResourceManager::GetShaderProgram( "Sprite" );
	if( !pSpriteShaderProgram )
	{
		std::cerr << "ERROR::Couldn't find sprite!\n";
		return false;
	}

	auto pTex = ResourceManager::LoadTexture( "map_16x16", "res/textures/map_16x16.png" );

	auto pTextureAtlas = ResourceManager::GetTexture( "DefaultTextureAtlas" );
	if( !pTextureAtlas )
	{
		std::cerr << "ERROR::Couldn't find texture atlas!\n";
		return false;
	}

	auto pAnimatedSprite = ResourceManager::LoadAnimatedSprite( "NewAnimatedSprite", "DefaultTextureAtlas", "Sprite", 100, 100, "concrete" );
	pAnimatedSprite->SetPosition( glm::vec2( 300, 300 ) );

	RenderEngine::AnimatedSprite::animFramesVector waterAnimations;
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water1", 1e9 ) );
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water2", 1e9 ) );
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water3", 1e9 ) );

	std::vector<std::pair<std::string, uint64_t>> eagleAnimations;
	eagleAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "eagle", 1e9 ) );
	eagleAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "deadEagle", 1e9 ) );

	pAnimatedSprite->InsertAnimation( "waterAnimation", std::move( waterAnimations ) );
	pAnimatedSprite->InsertAnimation( "eagleAnimation", std::move( eagleAnimations ) );

	pAnimatedSprite->SetAnimation( "waterAnimation" );

	RenderEngine::Renderer::SetClearColor( 0.f, 0.f, 0.f, 1.f );

	glm::mat4 modelMatrix_1 = glm::mat4( 1.f );
	modelMatrix_1 = glm::translate( modelMatrix_1, glm::vec3( 100.f, 200.f, 0.f ) );

	glm::mat4 modelMatrix_2 = glm::mat4( 1.f );
	modelMatrix_2 = glm::translate( modelMatrix_2, glm::vec3( 590, 400.f, 0.f ) );

	glm::mat4 orthoProjectionMatrix = glm::ortho( 0.f, (float)windowSize.x, 0.f, (float)windowSize.y, -100.f, 100.f );

	pSpriteShaderProgram->Use();

	Utils::ShaderHelper::SetInt( pSpriteShaderProgram->GetID(), "tex", 0 );
	Utils::ShaderHelper::SetMat4( pSpriteShaderProgram->GetID(), "projection", orthoProjectionMatrix );

	auto pTanksTextureAtlas = ResourceManager::GetTexture( "TanksTextureAtlas" );
	if( !pTanksTextureAtlas )
	{
		std::cerr << "ERROR::Couldn't find tank texture atlas!\n";
		return false;
	}
	auto pTanksAnimatedSprite = ResourceManager::GetAnimatedSprite( "TanksAnimatedSprite" );

	std::vector<std::pair<std::string, uint64_t>> tankTopState;
	tankTopState.emplace_back( std::make_pair<std::string, uint64_t>( "tankTop1", 5e8 ) );
	tankTopState.emplace_back( std::make_pair<std::string, uint64_t>( "tankTop2", 5e8 ) );

	std::vector<std::pair<std::string, uint64_t>> tankBottomState;
	tankBottomState.emplace_back( std::make_pair<std::string, uint64_t>( "tankBottom1", 5e8 ) );
	tankBottomState.emplace_back( std::make_pair<std::string, uint64_t>( "tankBottom2", 5e8 ) );

	std::vector<std::pair<std::string, uint64_t>> tankRightState;
	tankRightState.emplace_back( std::make_pair<std::string, uint64_t>( "tankRight1", 5e8 ) );
	tankRightState.emplace_back( std::make_pair<std::string, uint64_t>( "tankRight2", 5e8 ) );

	std::vector<std::pair<std::string, uint64_t>> tankLeftState;
	tankLeftState.emplace_back( std::make_pair<std::string, uint64_t>( "tankLeft1", 5e8 ) );
	tankLeftState.emplace_back( std::make_pair<std::string, uint64_t>( "tankLeft2", 5e8 ) );

	pTanksAnimatedSprite->InsertAnimation( "tankTopState", std::move( tankTopState ) );
	pTanksAnimatedSprite->InsertAnimation( "tankBottomState", std::move( tankBottomState ) );
	pTanksAnimatedSprite->InsertAnimation( "tankLeftState", std::move( tankLeftState ) );
	pTanksAnimatedSprite->InsertAnimation( "tankRightState", std::move( tankRightState ) );

	pTanksAnimatedSprite->SetAnimation( "tankTopState" );

	pTank = std::make_unique<Tank>( pTanksAnimatedSprite, 0.0000001f, glm::vec2( 100.f, 100.f ) );

	return true;
}
