
#include "MainManu.Class.hpp"

MainManu::MainManu(void): _width(1000), _height(1000)
{
    return;
}

MainManu::~MainManu(void)
{
    return;
}

int MainManu::StartWindow(void)
{

    if( !glfwInit() )
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 768, "BomberMan", NULL, NULL);
    if( window == NULL ){
        std::cout << "Failed to open GLFW window" ;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental=true;
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    Texture texture("title-jp.jpg");
  
	static const GLfloat g_vertex_buffer_data[] = { 
		
		1.0f, 1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,		0.0f, 0.0f, //1.0f, 0.0f
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, //0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,		1.0f, 1.0f //0.0f, 1.0f
	};
	GLuint indeces[] =
	{
		0,1,3,
		1,2,3
	};

	GLuint EBO;
	GLuint vertexbuffer;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);
        texture.Bind(0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			5 * sizeof(GLfloat),                  // stride
			(void*)0            // array buffer offset
		);

		// 1rst attribute buffer : texture
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

		
		// Draw the triangle !
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

    return(0);
}
int MainManu::getH(void) const
{
    return _height;
}
int MainManu::getW(void) const
{
    return _width;
}
void MainManu::setH(int height)
{
    this->_height = height;
    return;
}
void MainManu::setW(int width)
{
    this->_width = width;
    return;
}
enum
{
	TEXCOORD_VB,
};