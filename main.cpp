#include<shitcraft.h>

int main()
{
	window = glSetup();
	Camera* cam = Instantiate(new Camera);
	Camera::main = cam;
	
	Block *block = Instantiate(new Block);
	
	for (int i = 0; i <= 25; i++)
	{
		Block* spawned = Instantiate(new Block);
		spawned->transform.position = vec3(i, i, i);
		spawned->transform.euler = vec3(i, i, i);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateDeltaTime();
		UpdateTransforms();
		cam->DoInput(window, deltaTime);

		UpdateBlocks();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Cleanup();
	return 0;
}