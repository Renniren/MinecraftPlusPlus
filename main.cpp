#include<shitcraft.h>

bool generated;
int WORLD_SIZE = 15;
int WORLD_HEIGHT = 3;
int main()
{
	window = glSetup();
	Camera* cam = Instantiate(new Camera);
	Camera::main = cam;
	
	cam->position = vec3(0, 0, 5);


	vector<Block*> world = vector<Block*>();
	Chunk* chunk = new Chunk();
	Block* gen;
	vector<Block> blocks = vector<Block>();
	int count = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateDeltaTime();
		UpdateTransforms();
		cam->DoInput(window, deltaTime);
		//test->cube->position = -cam->position;

		if (!generated)
		{
			for (int x = 0; x <= WORLD_SIZE; x++)
			{
				for (int y = 0; y <= WORLD_HEIGHT; y++)
				{
					for (int z = 0; z <= WORLD_SIZE; z++)
					{
						count += x;
						if ((count) > Chunk::MaximumChunkSize)
						{
							(new Chunk())->init(blocks);
							blocks.clear();
							count = 0;
						}

						gen = new Block(false, true);
						gen->cube->position = vec3(x, y, z);
						gen->doDist = false;
						gen->draw = true;
						blocks.push_back(*gen);
					}
				}
			}
			
			generated = true;
		}
		//chunk->Draw();
		//UpdateBlocks();
		UpdateChunks();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Cleanup();
	return 0;
}