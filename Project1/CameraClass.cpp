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
		active = cameras.size();
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
		active = cameras.size();
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
		active = cameras.size();
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
		active = cameras.size();
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
		active = cameras.size();
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

	glm::mat4 Camera::getViewMatrix()
	{
		return cameras[active].view;
	}