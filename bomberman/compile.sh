g++ window.cpp MainManu.Class.cpp shader.cpp Texture.cpp stb_image.c -o window -I glfw/include/ -I glew/include -L glfw/lib -L glew/lib -lglfw -lGLEW \
	-framework OpenGL