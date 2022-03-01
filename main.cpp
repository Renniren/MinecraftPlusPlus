#include<shitcraft.h>

bool generated;
int WORLD_SIZE = 4;
int main()
{
	window = glSetup();
	Camera* cam = Instantiate(new Camera);
	Camera::main = cam;
	
	cam->position = vec3(0, 0, 5);

	Block* block = Instantiate(new Block);
	Block* block2 = Instantiate(new Block);
	block2->cube->position = vec3(0, 0, 1);

	vector<Block*> world = vector<Block*>();
	Block* gen;

	cout << world.size() << endl;
	cout << world.size() << endl;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateDeltaTime();
		UpdateTransforms();
		cam->DoInput(window, deltaTime);

		if (!generated)
		{
			for (int x = 0; x < WORLD_SIZE; x++)
			{
				for (int y = 0; y < WORLD_SIZE; y++)
				{
					for (int z = 0; z < WORLD_SIZE; z++)
					{
						gen = new Block();
						gen->cube->position = vec3(x, y, z);
						world.push_back(gen);
					}
				}
			}
			generated = true;
		}

		UpdateBlocks();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Cleanup();
	return 0;
}