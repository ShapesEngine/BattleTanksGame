#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Game/Game.h"
#include "Physics/PhysicsEngine.h"

// 13 pixels width and 14 pixels height, 16 in this case is the dimension of subtexture
glm::ivec2 windowSize( 13 * 16, 14 * 16 );
std::unique_ptr<Game> pGame = std::make_unique<Game>( windowSize );

void glfwWindowSizeCallback( GLFWwindow* window, int width, int height )
{
    windowSize.x = width;
    windowSize.y = height;

    const float level_aspect_ratio = static_cast<float>(pGame->GetCurrentLevelWidth()) / pGame->GetCurrentLevelHeight();
    uint32_t viewport_width = windowSize.x;
    uint32_t viewport_height = windowSize.y;
    uint32_t viewport_left_offset = 0u;
    uint32_t viewport_bottom_offset = 0u;

    if( (float)windowSize.x / windowSize.y > level_aspect_ratio )
    {
        viewport_width = uint32_t( windowSize.y * level_aspect_ratio );
        viewport_left_offset = ( windowSize.x - viewport_width ) / 2;
    }
    else
    {
		viewport_height = int( windowSize.x / level_aspect_ratio);
		viewport_bottom_offset = ( windowSize.y - viewport_height ) / 2;
    }

    RenderEngine::Renderer::SetViewport( viewport_width, viewport_height, viewport_left_offset, viewport_bottom_offset );
}

void glfwKeyCallback( GLFWwindow* pWindow, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( pWindow, GL_TRUE );

    pGame->SetKey(key, action);
}

int main( int argc, char** argv )
{
    /* Initialize the library */
    if ( !glfwInit() )
	{
        std::cout << "glfwInit failed!\n" << std::endl;
		return -1;
	}

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow( windowSize.x, windowSize.y, "Battle Tanks", nullptr, nullptr );
	if ( !pWindow )
    {
        std::cout << "glfwCreateWindow failed!\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback( pWindow, glfwWindowSizeCallback );
    glfwSetKeyCallback( pWindow, glfwKeyCallback );

    /* Make the window's context current */
    glfwMakeContextCurrent( pWindow );
	
	if ( !gladLoadGL() )
	{
		std::cout << "Can't initialize GLAD!" << "\n";
		return -1;
	}    
    
    // Getting executable location
    // ---------------------------
    ResourceManager::SetExecutablePath( *argv );  
    PhysicsEngine::Init();

	std::cout << "Renderer: " << RenderEngine::Renderer::GetRendererStr() << "\n";
	std::cout << "OpenGL Version: " << RenderEngine::Renderer::GetVersionStr() << "\n";   

	auto lastTime = std::chrono::high_resolution_clock::now();
	
	pGame->Init();
    glfwSetWindowSize( pWindow, 3 * int( pGame->GetCurrentLevelWidth() ), 3 * int( pGame->GetCurrentLevelHeight() ) );

    /* Loop until the user closes the window */
    while( !glfwWindowShouldClose( pWindow ) )
    {
		auto currentTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>( currentTime - lastTime ).count();
		lastTime = currentTime;
        pGame->Update( duration );
        PhysicsEngine::Update( duration );

        /* Render here */
        RenderEngine::Renderer::Clear();
        
        pGame->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers( pWindow );

        /* Poll for and process events */
        glfwPollEvents();
    }
    PhysicsEngine::Terminate();
    pGame = nullptr;
    // delete resource manager before destroying context, 
    // otherwise it may lead to crash of the application
    ResourceManager::UnloadAllResources();

    glfwTerminate();

    return 0;
}