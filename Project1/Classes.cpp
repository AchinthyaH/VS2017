#include "Classes.h"

//implementation of camera class

//constructor with no arguments
Camera::Camera()
{
	windowHeight = 600;
	windowWidth = 800;
	cam c;
	c.pos.x = 1.2f;
	c.pos.y = 1.2f;
	c.pos.z = 1.2f;
	c.eye.x = 0.0f;
	c.eye.y = 0.0f;
	c.eye.z = 0.0f;
	c.up.x = 0.0f;
	c.up.y = 0.0f;
	c.up.z = 1.0f;
	c.view = glm::lookAt(c.pos,c.eye,c.up);
	cameras.push_back(c);
	active = cameras.size() -1;
}

//constructor with 3 arguments: position, direction and up vector
Camera::Camera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up)
{
	windowHeight = 600;
	windowWidth = 800;
	cam c;
	c.pos = pos;
	c.eye = eye;
	c.up = up;
	c.view = glm::lookAt(c.pos, c.eye, c.up);
	cameras.push_back(c);
	active = cameras.size()-1;
}

//constructor with 5 arguments: position, direction and up vector, with window size parameters
Camera::Camera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up, GLuint wWidth, GLuint wHeight)
{
	windowHeight = wHeight;
	windowWidth = wWidth;
	cam c;
	c.pos = pos;
	c.eye = eye;
	c.up = up;
	c.view = glm::lookAt(c.pos, c.eye, c.up);
	cameras.push_back(c);
	active = cameras.size()-1;
}

//3 parameter function to add a new camera
void Camera::addCamera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up)
{
	windowHeight = 600;
	windowWidth = 800;
	cam c;
	c.pos = pos;
	c.eye = eye;
	c.up = up;
	c.view = glm::lookAt(c.pos, c.eye, c.up);
	cameras.push_back(c);
	active = cameras.size()-1;
}

//5 parameter function to add a new camera
void Camera::addCamera(glm::vec3 pos, glm::vec3 eye, glm::vec3 up, GLuint wWidth, GLuint wHeight)
{
	windowHeight = wHeight;
	windowWidth = wWidth;
	cam c;
	c.pos = pos;
	c.eye = eye;
	c.up = up;
	c.view = glm::lookAt(c.pos, c.eye, c.up);
	cameras.push_back(c);
	active = cameras.size()-1;
}

//choose which camera is active to perform transforms on it
void Camera::chooseCam(unsigned int x)
{
	active = x;
}

//rotate the active camera by the input angle
void Camera::rotateCam(float angle)
{
	cameras[active].view = glm::rotate(cameras[active].view, angle, cameras[active].up);
}

//rotate the active camera by the input angle about the specified axis
void Camera::rotateCam(float angle, glm::vec3 axis)
{
	cameras[active].view = glm::rotate(cameras[active].view, angle, axis);
}

//move the active camera by the specified distance in each direction
void Camera::translateCam(glm::vec3 displacement)
{
	cameras[active].view = glm::translate(cameras[active].view, displacement);
}

//return view matrix of active camera
glm::mat4 Camera::getViewMatrix()
{
	return cameras[active].view;
}

glm::vec3 Camera::getPos()
{
	return cameras[active].pos;
}

glm::vec3 Camera::getEye()
{
	return cameras[active].eye;
}

glm::vec3 Camera::getUp()
{
	return cameras[active].up;
}
//constructor with 2 arguments
Shaders::Shaders(string vShader, string fShader)
{
	vertexShader.push_back(vShader);
	fragmentShader.push_back(fShader);

}

//function to add a new vertex shader code
void Shaders::addVertexShader(string vShader)
{
	vertexShader.push_back(vShader);
}

//function to add a new fragment shader code
void Shaders::addFragmentShader(string fShader)
{
	fragmentShader.push_back(fShader);
}

//function to create and link program
void Shaders::createShaderProgram(unsigned int i, unsigned int j)
{
	// Create and compile the vertex shader
	vertexSource = (GLchar *) vertexShader[i].c_str();
	tempVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(tempVertexShader, 1, &vertexSource, NULL);
	glCompileShader(tempVertexShader);

	// Create and compile the fragment shader
	fragmentSource = (GLchar *)fragmentShader[j].c_str();
	tempFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(tempFragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(tempFragmentShader);

	// Link the vertex and fragment shader into a shader program
	tempShaderProgram = glCreateProgram();
	glAttachShader(tempShaderProgram, tempVertexShader);
	glAttachShader(tempShaderProgram, tempFragmentShader);
	glBindFragDataLocation(tempShaderProgram, 0, "outColor");
	glLinkProgram(tempShaderProgram);

	finalProgram.push_back(tempShaderProgram);
}

//return specified shader program
GLuint Shaders::getShaderProgram(unsigned int x)
{
	return finalProgram[x];
}

//delete specified vertex shader code
void Shaders::deleteVertexShader(unsigned int x)
{
	vertexShader.erase(vertexShader.begin() + x);
}

//delete specified fragment shader code
void Shaders::deleteFragmentShader(unsigned int x)
{
	fragmentShader.erase(fragmentShader.begin() + x);
}

//delete specified program
void Shaders::deleteProgram(unsigned int x)
{
	finalProgram.erase(finalProgram.begin() + x);
}

//clear all memory
void Shaders::deleteAll()
{
	vertexShader.clear();
	fragmentShader.clear();
	finalProgram.clear();
}
