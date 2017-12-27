#include "Header.h"
#include "Classes.h"

string cubeMapVertexSource = R"glsl(
	#version 330 core
	in vec3 aPos;
	in vec2 aTexCoords;

	out vec2 TexCoords;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
	    TexCoords = aTexCoords;    
	    gl_Position = proj * view * model * vec4(aPos, 1.0);
	}
)glsl";


string cubeMapFragmentSource = R"glsl(
	#version 330 core	
	out vec4 outColor;

	in vec2 TexCoords;

	uniform sampler2D texture1;

	void main()
	{    
	    outColor = texture(texture1, TexCoords);
	}
)glsl";

string skyboxVertexSource = R"glsl(
	#version 330 core
	in vec3 aPos;

	out vec3 TexCoords;

	uniform mat4 projection;
	uniform mat4 view;

	void main()
	{
		TexCoords = aPos;
		vec4 pos = projection * view * vec4(aPos, 1.0);
		gl_Position = pos.xyww;
	}  
)glsl";

string skyboxFragmentSource = R"glsl(
	#version 330 core
	out vec4 outColor;

	in vec3 TexCoords;

	uniform samplerCube skybox;

	void main()
	{    
	    outColor = texture(skybox, TexCoords);
	}
)glsl";

// Cube vertices
GLfloat cubeVertices[] = { 
	// positions          // texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

GLfloat skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char *data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SOIL_free_image_data(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		SOIL_free_image_data(data);
	}

	return textureID;
}


// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i].c_str() << std::endl;
			SOIL_free_image_data(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}


// These are now global variables so drawCubeScene() can access them
GLuint vaoCube, vboCube, vaoSkybox, vboSkybox;
GLint uniModel, uniView, uniProj;
SDL_GLContext context;
SDL_Window* window;
float x = 0;

Shaders S(cubeMapVertexSource, cubeMapFragmentSource);
Camera C(glm::vec3(3.0f, 2.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

void specifyCubeMapVertexAttributes(GLuint shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "aTexCoords");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	

}

void specifySkyboxVertexAttributes(GLuint shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

}


int main(int argc, char *argv[])
{

	// Create Context
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);


	// Inititialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);

	S.addVertexShader(skyboxVertexSource);
	S.addFragmentShader(skyboxFragmentSource);
	S.createShaderProgram(0, 0);
	S.createShaderProgram(1, 1);

	// Create VAOs
	glGenVertexArrays(1, &vaoCube);
	glGenVertexArrays(1, &vaoSkybox);

	// Load vertex data for cube
	glGenBuffers(1, &vboCube);
	glBindVertexArray(vaoCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	specifyCubeMapVertexAttributes(S.getShaderProgram(0));

	// Load vertex data for skybox
	glGenBuffers(1, &vboSkybox);
	glBindVertexArray(vaoSkybox);
	glBindBuffer(GL_ARRAY_BUFFER, vboSkybox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	specifySkyboxVertexAttributes(S.getShaderProgram(1));

	glm::vec3 camPosition = C.getPos();

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// load textures
	// -------------
	unsigned int cubeTexture = loadTexture("skybox/marble.jpg");
	vector<std::string> faces;
	faces.push_back("skybox/right.jpg");
	faces.push_back("skybox/left.jpg");
	faces.push_back("skybox/top.jpg");
	faces.push_back("skybox/bottom.jpg");
	faces.push_back("skybox/back.jpg");
	faces.push_back("skybox/front.jpg");

	unsigned int cubemapTexture = loadCubemap(faces);

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

		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 100.0f);
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

		glm::mat4 model;// = glm::mat4(1);
		uniModel = glGetUniformLocation(S.getShaderProgram(0), "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		// Draw cube
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//skybox
		glUseProgram(S.getShaderProgram(1));
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		view = glm::mat4(glm::mat3(C.getViewMatrix())); // remove translation from the view matrix

		uniView = glGetUniformLocation(S.getShaderProgram(1), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	
		uniProj = glGetUniformLocation(S.getShaderProgram(1), "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		// skybox cube
		glBindVertexArray(vaoSkybox);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

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