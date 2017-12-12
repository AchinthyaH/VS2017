#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#undef main
using namespace std;

void Create_Context();
void Init_GLEW();
void Create_Buffers();
void Create_Shaders();
void Get_Attributes();
void Load_Textures();
void Transform3D();
void Release_Resources();


extern SDL_GLContext context;
extern SDL_Window* window;
extern const GLchar* fragmentSource;
extern const GLchar* vertexSource;
extern GLuint vao;
extern GLuint vbo;
extern GLuint ebo;
extern GLuint textures[2];
extern GLuint vertexShader;
extern GLuint fragmentShader;
extern GLuint shaderProgram;
extern GLint uniModel;
extern GLint uniView;
extern GLint uniProj;
extern GLint uniColor;
extern float x;