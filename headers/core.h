#pragma once
#ifndef SHITCRAFT_CORE
#define SHITCRAFT_CORE

template<typename T>
inline T* Instantiate(T* to)
{
	T* n = new T();
	return n;
}

class WorldObject
{
public:
	virtual void Awake()
	{

	}

	virtual void Start()
	{

	}

	virtual void Update()
	{

	}

	virtual void LateUpdate()
	{

	}


	static vector<WorldObject> ActiveObjects;
	WorldObject()
	{
		ActiveObjects.push_back(*this);
		Awake();
		Start();
	}
};

class TestTriangle : public drawable
{

};

class Block : public WorldObject
{
protected:

public:
	Cube* cube;
	//vector<vec3> faces;
	static vector<Block*> ActiveBlocks;

	bool active = true;
	bool draw = true;
	bool doDist = true;
	bool dynamic = false;

	int parentChunk = 0;

	void Start()
	{
		
	}

	Block(bool draw = true, bool forChunk = true, int parent = 0)
	{
		cube = new Cube();
		this->draw = draw;
		if (forChunk)
		{
			cube->Initialize(1);
		}
		else
		{
			cube->Initialize(0);
		}
		ActiveBlocks.push_back(this);
	}

	void Update()
	{
		if(active && draw) cube->Draw(1);
		if (glfwGetKey(window, GLFW_KEY_Y))
		{
			if (dist(cube->position, Camera::main->position) < 1)
			{
				cout << "hello from Block " << parentChunk;
				printvec3(cube->position);
				cout << endl;
			}
		}
	}
};

vector<WorldObject> WorldObject::ActiveObjects = vector<WorldObject>();

vector<Block*> Block::ActiveBlocks = vector<Block*>();


void UpdateWorldObjects()
{
	for (int i = 0; i < WorldObject::ActiveObjects.size(); i++)
	{
		WorldObject::ActiveObjects[i].Update();
	}
}

void UpdateBlocks()
{
	for (int i = 0; i < Block::ActiveBlocks.size(); i++)
	{
		if(Block::ActiveBlocks[i] != nullptr) Block::ActiveBlocks[i]->Update();
	}
}

#endif