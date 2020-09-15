#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    /* Initialize the library */
    if ( !glfwInit() )
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow( 640, 480, "Hello World", NULL, NULL );
	if ( !window )
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent( window );
	
	if ( !gladLoadGL() )
	{
		std::cout << "Can't initialize GLAD!" << "\n";
		return -1;
	}
	
	std::cout << "OpenGL: " << GLVersion.major << "." << GLVersion.minor << "\n";	
	
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