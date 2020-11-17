#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Renderer/AnimatedSprite.h"
#include "Resources/ResourceManager.h"
#include "Utils/ShaderHelper.h"

glm::vec2 windowSize = { 640,480 };

void glfwWindowSizeCallback( GLFWwindow* window, int width, int height )
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport( 0, 0, windowSize.x, windowSize.y );
}

void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( window, GL_TRUE );
}

int main( int argc, char** argv )
{
    GLfloat vPos[] = {
		0.0f, 50.f, 0.0f,
		50.f, -50.f, 0.0f,
		-50.f, -50.f, 0.0f
    };

    GLfloat vCol[] = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };

	GLfloat tCoord[] = {
		0.5f, 1.f, 
		1.f, 0.f, 
		0.f, 0.f
	};

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
    ResourceManager* pRes = new ResourceManager( *argv );
    auto pBasicShaderProgram = pRes->LoadShaders( "Basic", "res/shaders/basic.vert", "res/shaders/basic.frag" );

    if( !pBasicShaderProgram )
        return -1;

	auto pSpriteShaderProgram = pRes->LoadShaders( "Sprite", "res/shaders/sprite.vert", "res/shaders/sprite.frag" );

	if( !pSpriteShaderProgram )
		return -1;

    auto pTex = pRes->LoadTexture( "map_16x16", "res/textures/map_16x16.png" );

	std::vector<std::string> subTexturesNames = {
		"block",
		"topBlock",
		"bottomBlock",
		"leftBlock",
		"rightBlock",
		"topLeftBlock",
		"topRightBlock",
		"bottomLeftBlock",

		"bottomRightBlock",
		"concrete",
		"topConcrete",
		"bottomConcrete",
		"leftConcrete",
		"rightConcrete",
		"topLeftConcrete",
		"topRightConcrete",

		"bottomLeftConcrete",
		"bottomRightConcrete",
		"water1",
		"water2",
		"water3",
		"trees",
		"ice",
		"wall",

		"eagle",
		"deadEagle",
		"nothing",
		"respawn1",
		"respawn2",
		"respawn3",
		"respawn4"
	};
	auto pTextureAtlas = pRes->LoadTextureAtlas( "DefaultTextureAtlas", "res/textures/map_16x16.png", std::move( subTexturesNames ), 16, 16 );

	auto pSprite = pRes->LoadSprite( "NewSprite", "DefaultTextureAtlas", "Sprite", 100, 100, "concrete" );
    pSprite->SetPosition( glm::vec2( 300, 100 ) );

	auto pAnimatedSprite = pRes->LoadAnimatedSprite( "NewAnimatedSprite", "DefaultTextureAtlas", "Sprite", 100, 100, "concrete" );
	pAnimatedSprite->SetPosition( glm::vec2( 300, 300 ) );

	Renderer::AnimatedSprite::animFramesVector waterAnimations;
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water1", 1e9 ) );
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water2", 1e9 ) );
	waterAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "water3", 1e9 ) );

	std::vector<std::pair<std::string, uint64_t>> eagleAnimations;
	eagleAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "eagle", 1e9 ) );
	eagleAnimations.emplace_back( std::make_pair<std::string, uint64_t>( "deadEagle", 1e9 ) );

	pAnimatedSprite->InsertAnimation( "waterAnimation", std::move( waterAnimations ) );
	pAnimatedSprite->InsertAnimation( "eagleAnimation", std::move( eagleAnimations ) );

	pAnimatedSprite->SetAnimation( "waterAnimation" );

    GLuint posVBO, colVBO, tCoordVBO;

    glGenBuffers( 1, &posVBO );
    glBindBuffer( GL_ARRAY_BUFFER, posVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vPos ), vPos, GL_STATIC_DRAW );

	glGenBuffers( 1, &colVBO );
	glBindBuffer( GL_ARRAY_BUFFER, colVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vCol ), vCol, GL_STATIC_DRAW );

	glGenBuffers( 1, &tCoordVBO );
    glBindBuffer( GL_ARRAY_BUFFER, tCoordVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( tCoord ), tCoord, GL_STATIC_DRAW );

    GLuint VAO;
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, posVBO );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	glEnableVertexAttribArray( 1 );
	glBindBuffer(GL_ARRAY_BUFFER, colVBO );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	glEnableVertexAttribArray( 2 );
	glBindBuffer( GL_ARRAY_BUFFER, tCoordVBO );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

	glClearColor( 0.f, 0.f, 0.f, 1.f );

    pBasicShaderProgram->Use();    

	glm::mat4 modelMatrix_1 = glm::mat4( 1.f );
	modelMatrix_1 = glm::translate( modelMatrix_1, glm::vec3( 100.f, 200.f, 0.f ) );

	glm::mat4 modelMatrix_2 = glm::mat4( 1.f );
	modelMatrix_2 = glm::translate( modelMatrix_2, glm::vec3( 590, 400.f, 0.f ) );

    glm::mat4 orthoProjectionMatrix = glm::ortho( 0.f, (float)windowSize.x, 0.f, (float)windowSize.y, -100.f, 100.f );

    Utils::ShaderHelper::SetInt( pBasicShaderProgram->GetID(), "tex", 0 );
    Utils::ShaderHelper::SetMat4( pBasicShaderProgram->GetID(), "projection", orthoProjectionMatrix );

	pSpriteShaderProgram->Use();

	Utils::ShaderHelper::SetInt( pSpriteShaderProgram->GetID(), "tex", 0 );
    Utils::ShaderHelper::SetMat4( pSpriteShaderProgram->GetID(), "projection", orthoProjectionMatrix );
    

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";   

	auto lastTime = std::chrono::high_resolution_clock::now();

    /* Loop until the user closes the window */
    while( !glfwWindowShouldClose( pWindow ) )
    {
		auto currentTime = std::chrono::high_resolution_clock::now();
		uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>( currentTime - lastTime ).count();
		lastTime = currentTime;
		pAnimatedSprite->Update( duration );

        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT );
        
        pBasicShaderProgram->Use();
		glBindVertexArray( VAO );
		pTex->Bind();        

        // wont bind projection as it will remain same
        Utils::ShaderHelper::SetMat4( pBasicShaderProgram->GetID(), "model", modelMatrix_1 );        
        glDrawArrays( GL_TRIANGLES, 0, 3);

		Utils::ShaderHelper::SetMat4( pBasicShaderProgram->GetID(), "model", modelMatrix_2 );        
		glDrawArrays( GL_TRIANGLES, 0, 3 );

        pSprite->Render();

		pAnimatedSprite->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers( pWindow );

        /* Poll for and process events */
        glfwPollEvents();
    }
    Renderer::Texture2D::Unbind();
    Renderer::ShaderProgram::Disuse();
    
    // delete resource manager before destroying context, 
    // otherwise it may lead to crash of the application
    delete pRes;

    glfwTerminate();

    return 0;
}