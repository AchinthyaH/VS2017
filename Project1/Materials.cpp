
#include "Header.h"
#include "Classes.h"

string cubeVertexSource = R"glsl(
	#version 330 core
	in vec3 aPos;
	in vec3 aNormal;
	

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;
	
	out vec3 fragPos;  
	out vec3 Normal;
	
	void main()
	{
		fragPos = vec3(view * model * vec4(aPos, 1.0));
		Normal = mat3(transpose(inverse(view * model))) * aNormal;
		gl_Position = proj * view * model * vec4(aPos, 1.0);
		
	}
)glsl";


string cubeFragmentSource = R"glsl(
	#version 330 core
	
	struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
	}; 
	
	struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	};	

	in vec3 Normal;
	in vec3 fragPos;
	
	uniform Material material;
	uniform Light light;
	
	out vec4 outColor;

	void main()
	{
		// ambient
		vec3 ambient = light.ambient * material.ambient;
    
		// diffuse 
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.poition - fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse *(diff * material.diffuse);
    
		// specular
		vec3 viewDir = normalize(-fragPos); 
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * (spec * material.specular); 
    
		vec3 result = ambient + diffuse + specular;
		outColor = vec4(result, 1.0);	
	}
)glsl";

string lightVertexSource = R"glsl(
	#version 330 core
	in vec3 aPos;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
		gl_Position = proj * view * model * vec4(aPos, 1.0);
	}
)glsl";

string lightFragmentSource = R"glsl(
	#version 330 core
	out vec4 outColor;

	void main()
	{
	outColor = vec4(1.0); // set all 4 vector values to 1.0
	}
)glsl";

// Cube vertices
GLfloat cubeVertices[] = {

	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// These are now global variables so drawCubeScene() can access them
GLuint vaoCube, vaoLight;
GLint uniModel, uniView, uniProj;
SDL_GLContext context;
SDL_Window* window;
float x = 0;

Shaders S(cubeVertexSource, cubeFragmentSource);
Camera C(glm::vec3(5.0f, 2.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

void specifyCubeVertexAttributes(GLuint shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint normAttrib = glGetAttribLocation(shaderProgram, "aNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(normAttrib);

}

void specifyLightVertexAttributes(GLuint shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

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

	// Create VAOs
	glGenVertexArrays(1, &vaoCube);
	glGenVertexArrays(1, &vaoLight);

	// Load vertex data
	GLuint vboCube;
	glGenBuffers(1, &vboCube);

	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);


	// lighting
	glm::vec3 lightPosition(2.0f, 1.5f, 0.0f); //(-2.0f, 1.0f , 1.0f);
	glm::vec3 camPosition = C.getPos();



	S.addVertexShader(lightVertexSource);
	S.addFragmentShader(lightFragmentSource);

	S.createShaderProgram(0, 0);
	S.createShaderProgram(1, 1);

	// Specify the layout of the vertex data
	glBindVertexArray(vaoCube);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	specifyCubeVertexAttributes(S.getShaderProgram(0));

	glBindVertexArray(vaoLight);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	specifyLightVertexAttributes(S.getShaderProgram(1));

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
		x = x + 0.25f;
		glm::vec3 LightColor;
		LightColor.x = sin(x * 2.0f);
		LightColor.y = sin(x * 0.7f);
		LightColor.z = sin(x * 1.3f);
		glm::vec3 diffuseColor = LightColor   * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

		GLint lightAmbient = glGetUniformLocation(S.getShaderProgram(0), "light.ambient");
		glUniform3fv(lightAmbient, 1, (GLfloat*)glm::value_ptr(ambientColor));
		GLint lightDiffuse = glGetUniformLocation(S.getShaderProgram(0), "light.diffuse");
		glUniform3fv(lightAmbient, 1, (GLfloat*)glm::value_ptr(diffuseColor));
		GLint lightSpecular = glGetUniformLocation(S.getShaderProgram(0), "light.specular");
		glUniform3fv(lightAmbient, 1, (GLfloat*)glm::value_ptr(specularColor));
		GLint lightPos = glGetUniformLocation(S.getShaderProgram(0), "lightPos");
		glUniform3fv(lightPos, 1, glm::value_ptr(lightPosition));


		GLint materialAmbient = glGetUniformLocation(S.getShaderProgram(0), "material.ambient");
		glUniform3f(materialAmbient, 1.0f, 0.5f, 0.31f);
		GLint materialDiffuse = glGetUniformLocation(S.getShaderProgram(0), "material.diffuse");
		glUniform3f(materialDiffuse, 1.0f, 0.5f, 0.31f);
		GLint materialSpecular = glGetUniformLocation(S.getShaderProgram(0), "material.specular");
		glUniform3f(materialSpecular, 0.5f, 0.5f, 0.5f);
		GLint materialShininess = glGetUniformLocation(S.getShaderProgram(0), "material.shininess");
		glUniform1f(materialSpecular, 64.0f);

		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 100.0f);
		uniProj = glGetUniformLocation(S.getShaderProgram(0), "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		glm::mat4 view = C.getViewMatrix();

		uniView = glGetUniformLocation(S.getShaderProgram(0), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));


		glm::mat4 model;
		model = glm::rotate(
			model,
			glm::radians(x),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);

		uniModel = glGetUniformLocation(S.getShaderProgram(0), "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		// Draw cube
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//light cube
		glBindVertexArray(vaoLight);
		glUseProgram(S.getShaderProgram(1));

		uniProj = glGetUniformLocation(S.getShaderProgram(1), "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		uniView = glGetUniformLocation(S.getShaderProgram(1), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 modelLight = glm::mat4();
		modelLight = glm::translate(modelLight, lightPosition);
		modelLight = glm::scale(modelLight, glm::vec3(0.2f));


		uniModel = glGetUniformLocation(S.getShaderProgram(1), "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelLight));


		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap buffers
		SDL_GL_SwapWindow(window);

	}


	S.deleteAll();

	glDeleteBuffers(1, &vboCube);

	glDeleteVertexArrays(1, &vaoCube);
	glDeleteVertexArrays(1, &vaoLight);
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;

}