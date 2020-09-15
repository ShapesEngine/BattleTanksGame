#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

int main(void)
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
	
    std::cout << "Renderer: " << glGetString( GL_RENDERER ) << "\n";
    std::cout << "OpenGL Version: " << glGetString( GL_VERSION ) << "\n";	
	
	glClearColor( 0, 1, 0, 1 );
	
    /* Loop until the user closes the window */
    while( !glfwWindowShouldClose( window ) )
    {
        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT );

        /* Swap front and back buffers */
        glfwSwapBuffers( window );

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}