#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

int windowWidth = 640;
int windowHeight = 480;

void glfwWindowSizeCallback( GLFWwindow* window, int width, int height )
{
    windowWidth = width;
    windowHeight = height;
    glViewport( 0, 0, windowWidth, windowHeight );
}

void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( window, GL_TRUE );
}

int main( int argc, char** argv )
{
    GLfloat vPos[] = {
        0.f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f
    };

    GLfloat vCol[] = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
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
    GLFWwindow* window = glfwCreateWindow( windowWidth, windowHeight, "Battle Tanks", nullptr, nullptr );
	if ( !window )
    {
        std::cout << "glfwCreateWindow failed!\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback( window, glfwWindowSizeCallback );
    glfwSetKeyCallback( window, glfwKeyCallback );

    /* Make the window's context current */
    glfwMakeContextCurrent( window );
	
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

    pRes->LoadTexture( "map_16x16", "res/textures/map_16x16.png" );

    GLuint posVBO, colVBO;

    glGenBuffers( 1, &posVBO );
    glBindBuffer( GL_ARRAY_BUFFER, posVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vPos ), vPos, GL_STATIC_DRAW );

	glGenBuffers( 1, &colVBO );
	glBindBuffer( GL_ARRAY_BUFFER, colVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vCol ), vCol, GL_STATIC_DRAW );

    GLuint VAO;
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, posVBO );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	glEnableVertexAttribArray( 1 );
	glBindBuffer(GL_ARRAY_BUFFER, colVBO );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	glClearColor( 0.f, 0.f, 0.f, 1.f );
    pBasicShaderProgram->Use();

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    /* Loop until the user closes the window */
    while( !glfwWindowShouldClose( window ) )
    {
        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT );
        
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers( window );

        /* Poll for and process events */
        glfwPollEvents();
    }

    Renderer::ShaderProgram::Disuse();

    // delete resource manager before destroying context, 
    // otherwise it may lead to crash of the application
    // -------------------------------------------------
    delete pRes;
    glfwTerminate();

    return 0;
}