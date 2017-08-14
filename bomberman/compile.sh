g++ window.cpp MainManu.Class.cpp shader.cpp Texture.cpp stb_image.c -o window -I glfw/3.2.1/include/ -I glew/2.1.0/include -L glfw/3.2.1/lib -L glew/2.1.0/lib -lglfw -lGLEW \
	-framework OpenGL