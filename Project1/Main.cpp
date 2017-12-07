#include "Header.h"

int main(int argc, char *argv[])
{

	Create_Context();
	Init_GLEW();
	Create_Buffers();
	Create_Shaders();
	Get_Attributes();
	Load_Textures();

	while (true)
	{
		SDL_Event windowEvent;

		while (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}


		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a rectangle from the 2 triangles using 6 indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers
		SDL_GL_SwapWindow(window);

	}

	Release_Resources();
	return 0;

}
