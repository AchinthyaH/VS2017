
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

		// Clear the screen to black
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

		
		glEnable(GL_STENCIL_TEST);

		// Draw floor
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDepthMask(GL_FALSE);
		glClear(GL_STENCIL_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 36, 6);


		// Draw cube reflection
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);

		model = glm::scale(
			glm::translate(model, glm::vec3(0, 0, -1)),
			glm::vec3(1, 1, -1)
		);
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

		glDisable(GL_STENCIL_TEST);

		
	// Swap buffers
		SDL_GL_SwapWindow(window);

	}

	Release_Resources();
	return 0;

}
