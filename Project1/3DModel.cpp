
#include "Header.h"

int main(int argc, char *argv[])
{

	Create_Context();
	Init_GLEW();
	Create_Buffers();
	Create_Shaders();
	Get_Attributes();
	Load_Textures();
	Transform3D();

	while (true)
	{
		SDL_Event windowEvent;

		while (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		float time = (float)SDL_GetTicks();

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate transformation
		x++;
		glm::mat4 model;
		model = glm::rotate(
			model,
			glm::radians(x),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		// Draw cube
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap buffers
		SDL_GL_SwapWindow(window);

	}

	Release_Resources();
	return 0;

}
