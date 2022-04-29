#pragma once
#ifndef SHITCRAFT_MAIN_HEADER
#define SHITCRAFT_MAIN_HEADER

#include <quickrender.h>
#include <core.h>

class Chunk
{
public:
	BufferObject buffer;
	VertexArrayObject vao;
	Triangle debug;

	vector<Block> blocks;

	static vector<Chunk*> Chunks;
	static int MaximumChunkSize;

	vec3 center;
	int id; //Represent each chunk with an int in order to make it easier to link blocks to chunks.

	void init(vector<Block> blocks = {})
	{
		if (blocks.size() > 0) this->blocks = blocks;
		debug.Initialize();
		debug.scale = onevec;
		Chunks.push_back(this);
		vec3 op = zerovec;
		vao.Generate(1);
		vao.Bind();

		buffer.Generate(GL_ARRAY_BUFFER);
		buffer.Bind(GL_ARRAY_BUFFER);

		for (size_t i = 0; i < this->blocks.size(); i++)
		{
			this->blocks[i].parentChunk = Chunks.size();
			buffer.Copy(GL_ARRAY_BUFFER, PRIMITIVE_CUBE, sizeof(PRIMITIVE_CUBE), GL_DYNAMIC_DRAW);
			op += this->blocks[i].cube->position;
			//cout << blocks[i].cube->position.x << ", " << blocks[i].cube->position.y << ", " << blocks[i].cube->position.z << endl;
		}
		op /= this->blocks.size();
		//op /= 2;
		center = op;
		debug.position = center;
		//cout << center.x << ", " << center.y << ", " << center.z << endl;
		VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
		VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (3 * sizeof(float)));
		ResetState();

	}

	void Draw()
	{
		for (size_t i = 0; i < this->blocks.size(); i++)
		{
			this->blocks[i].cube->texture->Bind(GL_TEXTURE_2D);
			Renderer::Draw(vao, this->blocks[i].cube->shaderProgram, buffer, *this->blocks[i].cube->wobj);
		}

	}
};



int Chunk::MaximumChunkSize = 32;
vector<Chunk*> Chunk::Chunks = vector<Chunk*>();

void UpdateChunks()
{

	for (size_t i = 0; i < Chunk::Chunks.size(); i++)
	{
		if (glfwGetKey(window, GLFW_KEY_Y))
		{
			cout << dist(Chunk::Chunks[i]->center, Camera::main->position) << endl;
		}

		if (dist(Camera::main->position, Chunk::Chunks[i]->center) > 3)
		{
			Chunk::Chunks[i]->Draw();
		}
	}
}

#endif