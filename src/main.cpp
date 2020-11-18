#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Game/Game.h"

glm::vec2 windowSize = { 640,480 };
Game game( windowSize );

void glfwWindowSizeCallback( GLFWwindow* window, int width, int height )
{
    windowSize.x = width;
    windowSize.y = height;
    RenderEngine::Renderer::SetViewport( width, height );
}

void glfwKeyCallback( GLFWwindow* pWindow, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( pWindow, GL_TRUE );

    game.SetKey(key, action);
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

	std::cout << "Renderer: " << RenderEngine::Renderer::GetRendererStr() << "\n";
	std::cout << "OpenGL Version: " << RenderEngine::Renderer::GetVersionStr() << "\n";   

	auto lastTime = std::chrono::high_resolution_clock::now();
	
	game.Init();

    /* Loop until the user closes the window */
    while( !glfwWindowShouldClose( pWindow ) )
    {
		auto currentTime = std::chrono::high_resolution_clock::now();
		uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>( currentTime - lastTime ).count();
		lastTime = currentTime;
        game.Update( duration );

        /* Render here */
        RenderEngine::Renderer::Clear();
        
        game.Render();

        /* Swap front and back buffers */
        glfwSwapBuffers( pWindow );

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    // delete resource manager before destroying context, 
    // otherwise it may lead to crash of the application
    ResourceManager::UnloadAllResources();

    glfwTerminate();

    return 0;
}