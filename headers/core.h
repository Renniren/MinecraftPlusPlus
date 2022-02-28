#pragma once
#ifndef SHITCRAFT_CORE
#define SHITCRAFT_CORE

template<typename T>
T* Instantiate(T* to)
{
	return new T(30);
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

class Block : public WorldObject
{
protected:
	Cube* cube;

public:
	Transform transform;
	
	static vector<Block*> ActiveBlocks;

	void Start()
	{
		
	}

	Block()
	{
		cube = new Cube();
		cube->Initialize();
		ActiveBlocks.push_back(this);
	}

	void Update()
	{
		cube->Draw(1);
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
		Block::ActiveBlocks[i]->Update();
	}
}

#endif