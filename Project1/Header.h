#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <iostream>
#include <vector>
#undef main
using namespace std;


struct cam
{
	glm::vec3 pos, eye, up;
	glm::mat4 view;

};

class Camera
{
protected:
	GLuint windowHeight, windowWidth;
	vector <cam> cameras;
	unsigned int active = 0;

public:

	Camera();
	Camera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up);
	Camera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up, GLuint wWidth, GLuint wHeight);
	void addCamera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up);
	void addCamera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up, GLuint wWidth, GLuint wHeight);
	void chooseCam(unsigned int x);
	void rotateCam(float angle);
	void rotateCam(float angle, glm::vec3 axis);
	void translateCam(glm::vec3 displacement);
	glm::mat4 getViewMatrix();
};

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
