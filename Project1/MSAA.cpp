#include "Header.h"
#include "Classes.h"

string VertexSource = R"glsl(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
		gl_Position = proj * view * model * vec4(aPos, 1.0);
	}
)glsl";



string FragmentSource = R"glsl(
	#version 330 core
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	} 
)glsl";


// Cube vertices
GLfloat cubeVertices[] = {
	// Positions       
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};

// These are now global variables so drawCubeScene() can access them
GLuint vaoCube, vboCube, vaoSkybox, vboSkybox;
GLint uniModel, uniView, uniProj;
SDL_GLContext context;
SDL_Window* window;
float x = 0;

Shaders S(VertexSource, FragmentSource);
Camera C(glm::vec3(3.0f, 1.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


int main(int argc, char *argv[])
{

	// Create Context
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);


	// Inititialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	S.createShaderProgram(0, 0);

	// cube VAO
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	glm::vec3 camPosition = C.getPos();

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	while (true)
	{
		SDL_Event windowEvent;

		while (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		//clear the screen to black
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(S.getShaderProgram(0));
		glBindVertexArray(vaoCube);

		glm::mat4 proj = glm::perspective(glm::radians(30.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
		uniProj = glGetUniformLocation(S.getShaderProgram(0), "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		glm::mat4 view = C.getViewMatrix();
		uniView = glGetUniformLocation(S.getShaderProgram(0), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		/*
		x = x + 0.25f;
		glm::mat4 model;
		model = glm::rotate(
		model,
		glm::radians(x),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
		*/

		glm::mat4 model;
		uniModel = glGetUniformLocation(S.getShaderProgram(0), "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap buffers
		SDL_GL_SwapWindow(window);

	}


	S.deleteAll();

	glDeleteVertexArrays(1, &vaoCube);
	glDeleteVertexArrays(1, &vaoSkybox);
	glDeleteBuffers(1, &vboCube);
	glDeleteBuffers(1, &vboSkybox);

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;

}