#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include <stdio.h>
#include <iostream>
#include "Texture.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class MainManu
{
    private:
        int _height;
        int _width;
        int _texcoord;
    public:
        MainManu(void);
        ~MainManu(void);
        int StartWindow(void);
        int getH(void) const;
        int getW(void) const;
        void setH(int Hght);
        void setW(int Wdth);
};
