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

	vector<Block> blocks = vector<Block>();

	static vector<Chunk*> Chunks;
	static int MaximumChunkSize;

	vec3 center;
	int id; //Represent each chunk with an int in order to make it easier to link blocks to chunks.

	Chunk()
	{
		id = Chunks.size();
	}

	void regenchunk()
	{
		debug.Initialize();
		debug.scale = onevec;
		vec3 op = zerovec;
		vao.Generate(1);
		vao.Bind();

		id = Chunks.size();
		cout << "Regenerated chunk with ID " << id << endl;
		buffer.Generate(GL_ARRAY_BUFFER);
		buffer.Bind(GL_ARRAY_BUFFER);

		for (size_t i = 0; i < this->blocks.size(); i++)
		{
			this->blocks[i].parentChunk = id;
			cout << "Chunk assigned Block an ID of " << this->blocks[i].parentChunk << endl;
			buffer.Copy(GL_ARRAY_BUFFER, PRIMITIVE_CUBE, sizeof(PRIMITIVE_CUBE), GL_DYNAMIC_DRAW);
			vec3 other = this->blocks[i].cube->position;
			op += other;
			//op /= 2;
			//cout << blocks[i].cube->position.x << ", " << blocks[i].cube->position.y << ", " << blocks[i].cube->position.z << endl;
		}
		op /= this->blocks.size();
		center = op;
		//debug.position = center;
		//cout << center.x << ", " << center.y << ", " << center.z << endl;
		VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
		VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (3 * sizeof(float)));
		ResetState();
	}

	void init()
	{
		debug.Initialize();
		debug.scale = onevec;
		Chunks.push_back(this);
		vec3 op = zerovec;
		vao.Generate(1);
		vao.Bind();

		id = Chunks.size();
		cout << "Created chunk with ID " << id << endl;

		buffer.Generate(GL_ARRAY_BUFFER);
		buffer.Bind(GL_ARRAY_BUFFER);

		for (size_t i = 0; i < this->blocks.size(); i++)
		{
			this->blocks[i].parentChunk = id;
			cout << "Chunk assigned Block an ID of " << this->blocks[i].parentChunk << endl;

			buffer.Copy(GL_ARRAY_BUFFER, PRIMITIVE_CUBE, sizeof(PRIMITIVE_CUBE), GL_DYNAMIC_DRAW);
			vec3 other = this->blocks[i].cube->position;
			op += other;
			//op /= 2;
			//cout << blocks[i].cube->position.x << ", " << blocks[i].cube->position.y << ", " << blocks[i].cube->position.z << endl;
		}
		op /= this->blocks.size();
		center = op;
		//debug.position = center;
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



int Chunk::MaximumChunkSize = 4;
vector<Chunk*> Chunk::Chunks = vector<Chunk*>();

void UpdateChunks()
{
	for (size_t i = 0; i < Chunk::Chunks.size(); i++)
	{
		if (glfwGetKey(window, GLFW_KEY_Y))
		{
			//cout << dist(Chunk::Chunks[i]->center, Camera::main->position) << endl;
		}
		
		//Chunk::Chunks[i]->debug.Draw();
			Chunk::Chunks[i]->Draw();
		if (dist(Camera::main->position, -Chunk::Chunks[i]->center) < 7)
		{
		}
	}
}

Chunk* GetChunkByID(int query)
{
	for (size_t i = 0; i < Chunk::Chunks.size(); i++)
	{
		if (Chunk::Chunks[i]->id == query) return Chunk::Chunks[i];
	}

	std::cout << "Could not find chunk with ID " << query << "." << endl;
	return nullptr;
}

#endif