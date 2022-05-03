#include<shitcraft.h>

bool generated;
const int WORLD_SIZE = 10;
const int WORLD_OFFSET = 0;
const int WORLD_HEIGHT = 3;
const int WORLD_MINIMUM_Y = -5;


int main()
{
	srand(time(0));
	window = glSetup();
	Camera* cam = Instantiate(new Camera);
	Camera::main = cam;
	
	cam->position = vec3(0, -WORLD_HEIGHT, 0);
	cam->rotation = vec3(0, 0, 0);
	cam->UpdateCameraMatrices();

	vector<Block*> world = vector<Block*>();
	Chunk* chunk = new Chunk();
	Block* gen;
	vector<Block> blocks = vector<Block>();
	int countx = 0, countz = 0;

	
	int map[WORLD_SIZE][WORLD_HEIGHT][WORLD_SIZE];
	for (size_t x = 0; x < WORLD_SIZE; x++)
	{
		for (size_t z = 0; z < WORLD_SIZE; z++)
		{
			for (size_t y = 0; y < WORLD_HEIGHT; y++)
			{
				map[x][y][z] = (int)(rand() % 5);
			}
		}
	}


	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateDeltaTime();
		UpdateTransforms();
		cam->DoInput(window, deltaTime);
		//test->cube->position = -cam->position;

		if (glfwGetKey(window, GLFW_KEY_T))
		{
			std::cout << "Camera Position: ";
			printvec3(cam->position);
			std::cout << std::endl;
			std::cout << "Blocks: " << world.size() << endl;
		}

		bool made_first_chunk = false;

		//Pretty inefficient. Don't know a better way to do it though.
		if (!generated)
		{
			for (int x = 0; x <= WORLD_SIZE; x++)
			{
				for (int z = 0; z <= WORLD_SIZE; z++)
				{
					for (int y = 0; y <= WORLD_HEIGHT; y++)
					{
						//y += sin(y) * 2;
						countx++;
						countz++;
						if (countx > Chunk::MaximumChunkSize && countz > Chunk::MaximumChunkSize)
						{
							chunk->blocks = blocks;
							chunk->init();
							//chunk->center = vec3(x, y, z);
							blocks.clear();
							countx = 0;
							countz = 0;
							chunk = new Chunk();
							made_first_chunk = true;
						}

						gen = new Block(false, true);
						gen->parentChunk = chunk->id;
						gen->cube->position = vec3(x, (y + WORLD_OFFSET) + map[x][y][z], z);
						gen->doDist = false;
						gen->draw = false;

						for (size_t i = WORLD_MINIMUM_Y; i < gen->cube->position.y; i++)
						{
							/*gen = new Block(true, false);
							gen->cube->position = vec3(world[i]->cube->position.x, x, world[i]->cube->position.z);
							gen->doDist = false;
							gen->draw = false;
							world.push_back(gen);
							blocks.push_back(*gen);*/
						}

						if (gen->cube->position.y < WORLD_MINIMUM_Y || gen->cube->position.y == -8.58993e+08)
						{
							std::cout << "fuck off" << endl;
							gen->cube->position.y = WORLD_MINIMUM_Y;
						}
						world.push_back(gen);
						blocks.push_back(*gen);
					}
				}
			}
			std::cout << "Generated world." << endl;
			cam->position = world[0]->cube->position;

			//std::cout << "Offsetting blocks..." << endl;
			//int amt = world.size();

			//std::cout << "Filling holes..." << endl;
			//for (size_t i = 0; i < amt; i++)
			//{
			//	for (int x = WORLD_MINIMUM_Y; x < (int)world[i]->cube->position.y; x++)
			//	{
			//		gen = new Block(true, false);
			//		gen->cube->position = vec3(world[i]->cube->position.x, x, world[i]->cube->position.z);
			//		gen->doDist = false;
			//		gen->draw = true;
			//		world.push_back(gen);
			//		//GetChunkByID(world[i]->parentChunk)->blocks.push_back(gen);
			//		//GetChunkByID(world[i]->parentChunk)->regenchunk();

			//		if (gen->cube->position.y < WORLD_MINIMUM_Y) gen->cube->position.y = WORLD_MINIMUM_Y;
			//	}
			//}

			
			
			generated = true;
		}
		//chunk->Draw();
		UpdateBlocks();
		UpdateChunks();
		//cam->UpdateCameraMatrices();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//free(map);
	//delete(map)
	Cleanup();
	return 0;
}