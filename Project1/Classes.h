#pragma once
#include "Header.h"

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

class Shaders
{
	vector <string> vertexShader, fragmentShader;
	vector <GLuint> finalProgram;
	GLchar* vertexSource, *fragmentSource;
	GLuint tempVertexShader, tempFragmentShader, tempShaderProgram;
public:
	Shaders(string vShader, string fShader);
	void createShaderProgram(unsigned int i, unsigned int j);
	void addVertexShader(string vShader);
	void addFragmentShader(string fShader);
	GLuint getShaderProgram(unsigned int x);
	void deleteVertexShader(unsigned int x);
	void deleteFragmentShader(unsigned int x);
	void deleteProgram(unsigned int x);
	void deleteAll();
};
