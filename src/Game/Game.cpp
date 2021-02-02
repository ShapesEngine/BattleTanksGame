#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Renderer.h"
#include "../Resources/ResourceManager.h"
#include "../System/Utils/ShaderHelper.h"
#include "../Physics/PhysicsEngine.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game( const glm::ivec2& windowSize ) :
    windowSize( windowSize )
{}

void Game::Render()
{
	if( pTank )
	{
		pTank->Render();
	}
	if( pLevel )
	{
		pLevel->Render();
	}
}

void Game::Update( double delta )
{
	if( pLevel )
	{
		pLevel->Update( delta );
	}

	if( pTank )
	{
		pTank->SetVelocity( 0.f );
		if( keys[GLFW_KEY_W] )
		{
			pTank->SetOrientation( Tank::EOrientation::Top );
			pTank->SetVelocity( pTank->GetMaxVelocity() );
		}
		if( keys[GLFW_KEY_S] )
		{
			pTank->SetOrientation( Tank::EOrientation::Bottom );
			pTank->SetVelocity( pTank->GetMaxVelocity() );
		}
		if( keys[GLFW_KEY_A] )
		{
			pTank->SetOrientation( Tank::EOrientation::Left );
			pTank->SetVelocity( pTank->GetMaxVelocity() );
		}
		if( keys[GLFW_KEY_D] )
		{
			pTank->SetOrientation( Tank::EOrientation::Right );
			pTank->SetVelocity( pTank->GetMaxVelocity() );
		}
		if( pTank && keys[GLFW_KEY_ENTER] )
		{
			pTank->Fire();
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
	ResourceManager::LoadJSONResources( "res/resources.json" );
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

	RenderEngine::Renderer::SetClearColor( 0.f, 0.f, 0.f, 1.f );
	RenderEngine::Renderer::SetDepthBuffer( true );

	glm::mat4 modelMatrix_1 = glm::mat4( 1.f );
	modelMatrix_1 = glm::translate( modelMatrix_1, glm::vec3( 100.f, 200.f, 0.f ) );

	glm::mat4 modelMatrix_2 = glm::mat4( 1.f );
	modelMatrix_2 = glm::translate( modelMatrix_2, glm::vec3( 590, 400.f, 0.f ) );

	pLevel = std::make_shared<Level>( ResourceManager::GetLevels()[0] );
	windowSize.x = (int)GetCurrentLevelWidth();
	windowSize.y = (int)GetCurrentLevelHeight();
	Physics::PhysicsEngine::SetCurrentLevel( pLevel );

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
	pTank = std::make_shared<Tank>( 0.05f, pLevel->GetPlayerRespawn_1Pos(), glm::vec2( Level::BLOCK_SIZE, Level::BLOCK_SIZE ) );
	Physics::PhysicsEngine::AddDynamicGameObject( pTank );

	return true;
}
