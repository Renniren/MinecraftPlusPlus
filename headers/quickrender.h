#ifndef QUICKRENDER_MAIN_HEADER
#define QUICKRENDER_MAIN_HEADER

#define STB_IMAGE_IMPLEMENTATION

#pragma once

#include <glad.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <glfw3.h>
#include <stdlib.h>
#include <direct.h>
#include <fstream>
#include <glm.hpp>
#include <sstream>
#include <iostream>
#include <stb_image.h>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef QUICKRENDER_MACROS
#define QUICKRENDER_MACROS

#define pragmatism __debugbreak(); 
#define panic __debugbreak();
#define PI 3.14f

#define uint unsigned int
#define onevec vec3(1,1,1)
#define zerovec vec3(0,0,0)
#define zeroqua qua(0,0,0,0)
#define cstring const char*

static bool glPrintErrors(const char* function, const char* file, int line)
{
	using namespace std;
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		while (err != GL_NO_ERROR)
		{
			const char* strerror = "";
			switch (err)
			{
			case 1280:
				strerror = "Invalid enum";
				break;
			case 1281:
				strerror = "Invalid value";
				break;
			case 1282:
				strerror = "Invalid operation";
				break;


			case 1285:
				strerror = "OpenGL ran out of memory";
				break;
			}

			cout << strerror << " in function " << function << " in file " << file << " on line " << line << endl;
			return false;
		}
	}
	return true;
}


#define STOP_ON_FAILURE(x) if ((!x)) __debugbreak();

#define glCall(x)\
	x;\
	STOP_ON_FAILURE(glPrintErrors(#x, __FILE__, __LINE__));

void PrintErrors()
{
	using namespace std;
	GLenum err = glGetError();

	if (err == 0) return;

	switch (err)
	{
	case 1280:
		cout << "Error: 1280 - Invalid enum. Perhaps you used an enum where it shouldn't be?" << endl;
		break;

	case 1281:
		cout << "Error: 1281 - Invalid value. Perhaps you passed the wrong type of data somewhere?" << endl;
		break;

	case 1282:
		cout << "Error: 1282 - Invalid operation." << endl;
		break;

	case 1283:
		cout << "Error: 1283 - stack overflow." << endl;
		break;

	case 1284:
		cout << "Error: 1284 - stack... underflow? How the fuck did you even do that?" << endl;
		break;

	case 1285:
		cout << "Error: 1285 - OpenGL ran out of memory." << endl;
		break;

	case 1286:
		cout << "Error: 1286 - Invalid framebuffer read/write." << endl;
		break;
	}

}

#endif

#ifndef QR_SETTINGS
#define QR_SETTINGS

int width = 800, height = 600;
const char* WINDOW_NAME = "Game";

#endif

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";


using namespace std;
using namespace glm;

inline void printvec3(vec3 op)
{
	cout << "(" << op.x << ", " << op.y << ", " << op.z << ")" << endl;
}


char* GetWorkingDirectory()
{
	char cCurrentPath[FILENAME_MAX];

	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		return nullptr;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '/0'; /* not really required */
	return cCurrentPath;
}

string TEXTURES_DIRECTORY = string(GetWorkingDirectory()) + string("\\textures\\");
string SHADERS_DIRECTORY = string(GetWorkingDirectory()) + string("\\shaders\\");
#ifndef QR_PRIMITIVES
#define QR_PRIMITIVES
float PRIMITIVE_CUBE[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
float PRIMITIVE_TRIANGLE[] = {
				-0.5f, -0.5f, 0.0f, // left  
				0.5f, -0.5f, 0.0f, // right 
				0.0f,  0.5f, 0.0f,
};
#endif

inline void ResetState()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_1D, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_3D, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}

inline vec3 InvertYPosition(vec3 op)
{
	return vec3(op.x, -op.y, op.z);
}

void ViewResizeCallback(GLFWwindow* window, int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
}

float MouseX, MouseY;
float lastX, lastY;
bool firstMouse = true;

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{

	
}

inline float dist(vec3 a, vec3 b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

GLFWwindow* glSetup()
{
	stbi_set_flip_vertically_on_load(true);
	
	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(width, height, WINDOW_NAME, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetFramebufferSizeCallback(window, ViewResizeCallback);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	return window;
}

class GLObject
{
	
public:

	uint id = -1;

	GLObject()
	{
		objects.push_back(*this);
	}

	virtual string ToString()
	{
		string result;
		stringstream ss;
		ss << id;
		ss >> result;
		return result;
	}

	virtual void Delete()
	{

	}

	GLObject* globj = this;
	static vector<GLObject> objects;
};

void Cleanup()
{
	for (int i = 0; i < GLObject::objects.size(); i++)
	{
		GLObject::objects[i].Delete();
	}

	glfwTerminate();
}

class Transform 
{
public:

	vec3 position = zerovec;
	quat rotation = quat(0,0,0,0);
	vec3 scale = zerovec;

	mat4 model = mat4(1.0f);

	vec3 forward = zerovec, right = zerovec, up = zerovec;
	
	bool BelongsToCamera = false;

	Transform()
	{
		ActiveTransforms.push_back(*this);
	}

	void UpdateDirections()
	{
		if (BelongsToCamera)
		{
			forward.x = cos(rotation.x) * sin(-rotation.y);
			forward.y = sin(rotation.z);
			forward.z = cos(rotation.x) * cos(-rotation.y);
		}
		else
		{
			forward.x = cos(-rotation.x) * sin(rotation.y);
			forward.y = sin(rotation.x);
			forward.z = cos(-rotation.x) * cos(rotation.y);
		}

		right.x = cos(rotation.y);
		right.y = 0;
		right.z = sin(rotation.y);

		up = cross(forward, right);
	}

	void UpdateMatrices()
	{
		UpdateDirections();
		if (BelongsToCamera)
		{
			model = translate(model, position);
			model = rotate(model, rotation.x, right);
			model = rotate(model, rotation.y, up);
			model = rotate(model, rotation.z, forward);
		}
		else                                       
		{
			model = translate(model, position);
			model = rotate(model, rotation.x, right);
			model = rotate(model, rotation.y, up);
			model = rotate(model, rotation.z, forward);
		}
		
		model = glm::scale(model, scale);
	}

	Transform* wobj = this;

	static vector<Transform> ActiveTransforms;
};

struct Light
{
	static vector<Light*> Lights;
	vec3 position;
	vec3 color;
	float range;
	float intensity;
	float specularIntensity;
	bool enabled, castShadows;

	Light(vec3 at, vec3 color, float range, float intensity, float specint, bool shadows = true)
	{
		this->position = at;
		this->color = color;
		this->range = range;
		this->intensity = intensity;
		this->specularIntensity = specint;
		this->castShadows = shadows;
		this->enabled = true;

		Lights.push_back(this);
	}
};

class Shader : public GLObject
{
public:

	cstring SourceCode = "";
	GLenum type = 0;

	Shader(cstring code, GLenum type)
	{
		this->SourceCode = code;
		this->type = type;
	}

	void CreateShader()
	{
		this->id = glCreateShader(this->type);
	}



	void LinkCode(cstring code)
	{
		SourceCode = code;
		glShaderSource(this->id, 1, &SourceCode, NULL);
	}

	void LinkCodeWithPath(string path)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::ifstream vShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(path);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			vShaderFile.close();
			vertexCode = vShaderStream.str();
			SourceCode = vertexCode.c_str();
			glShaderSource(this->id, 1, &SourceCode, NULL);
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Could not successfully read the shader's file: " << e.what() << std::endl;
		}
	}

	void Compile()
	{
		glCompileShader(this->id);
	}

	void Delete()
	{
		glDeleteShader(id);
	}
};

class ShaderProgram : public GLObject
{
public:
	vector<Shader> linkedShaders;
	bool initialized;

	void InitializeProgram(const vector<Shader>& shaders)
	{
		if (initialized)
		{
			glDeleteProgram(id);
			initialized = false;
		}

		this->id = glCreateProgram();
		for (int i = 0; i < shaders.size(); i++)
		{
			glAttachShader(this->id, shaders[i].id);
		}
		glLinkProgram(this->id);
		initialized = true;
	}

	void UseProgram() const
	{
		glUseProgram(this->id);
	}

	void setFloat(const string& name, const float& number) const
	{
		glUseProgram(id);
		glUniform1f(glGetUniformLocation(this->id, name.c_str()), number);
	}

	void setVec4(const string& name, const vec4& vect) const
	{
		glUseProgram(id);
		glUniform4f(glGetUniformLocation(this->id, name.c_str()), (GLfloat)vect.x, (GLfloat)vect.y, (GLfloat)vect.z, (GLfloat)vect.w);
	}

	void setVec3(const string& name, const vec3& vect) const
	{
		glUseProgram(id);
		glUniform3f(glGetUniformLocation(this->id, name.c_str()), (GLfloat)vect.x, (GLfloat)vect.y, (GLfloat)vect.z);
	}

	void setLight(const Light& light)
	{
		
	}

	void setMat4(const string& name, const glm::mat4& mat) const
	{
		glUseProgram(id);
		glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Delete()
	{
		glDeleteProgram(id);
	}
};

class VertexArrayObject : protected GLObject
{
public:
	int size;
	VertexArrayObject()
	{
		size = 0;
	}

	void Generate(int size)
	{
		this->size = size;
		glGenVertexArrays(size, &this->id);
	}


	void Bind()
	{
		glBindVertexArray(this->id);
	}

	void Delete()
	{
		glDeleteVertexArrays(size, &id);
	}
};

class BufferObject : public GLObject
{
public:
	GLenum buffer = 0;
	GLenum drawType = 0;

	int size = 0;
	void* data = nullptr;

	BufferObject()
	{
		buffer = 0;
		drawType = 0;
		size = 0;
		data = nullptr;
	}

	void Generate(GLenum buffer) 
	{
		this->buffer = buffer;
		glGenBuffers(1, &this->id);
	}

	void Bind(GLenum toWhat)
	{
		glBindBuffer(toWhat, this->id);
	}
	
	void Copy(GLenum buffer, void* data, int size, GLenum drawType)
	{
		this->data = data;
		this->drawType = drawType;
		this->buffer = buffer;
		this->size = size;

		glBindBuffer(buffer, this->id);
		glBufferData(buffer, this->size, data, drawType);
		PrintErrors();
	}

	void Delete()
	{
		glDeleteBuffers(size, &id);
	}
};

class Camera : public Transform
{
public:
	enum projectionMode { Perspective, Orthographic };
	float FieldOfView = 90, FarClip = 1000, NearClip = 0.01f;
	Camera::projectionMode ProjectionMode = Camera::projectionMode::Perspective;
	
	mat4 view = mat4(1), projection = mat4(1);


	Camera() 
	{
		this->BelongsToCamera = true;
		this->ProjectionMode = projectionMode::Perspective;
		this->FieldOfView = 90;
		this->FarClip = 1000;
		this->NearClip = 0.01f;

		this->view = mat4(1);
		this->projection = mat4(1);
	}

	Camera(Camera::projectionMode mode, bool makeMain, float fov = 90, float fc = 1000, float nc = 0.01f)
	{
		this->BelongsToCamera = true;
		this->ProjectionMode = mode;
		
		if (makeMain) main = this;
		this->FieldOfView = fov;
		this->FarClip = fc;
		this->NearClip = nc;

		this->view = mat4(1);
		this->projection = mat4(1);	
	}

	void DoInput(GLFWwindow* window, float deltaTime)
	{
		float speed = 1.9f;
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			position -= (forward * speed) * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_S))
		{
			position += (forward * speed) * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_A))
		{
			position -= (right * speed) * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			position += (right * speed) * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_E))
		{
			position.y += speed * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			position.y -= speed * deltaTime;
		}

		UpdateDirections();
		
		if (glfwGetKey(window, GLFW_KEY_C))
		{
			rotation.y -= speed * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			rotation.y += speed * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_X))
		{
			rotation.z += speed * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_V))
		{
			rotation.z -= speed* deltaTime;
		}
	}

	void UpdateCameraMatrices()
	{
		/*view = rotate(view, rotation.x, vec3(0, 0, 1));
		view = rotate(view, rotation.y, vec3(0, 1, 0));
		view = rotate(view, rotation.z, vec3(1, 0, 0));*/
		UpdateDirections();
		view = rotate(view, rotation.x, right);
		view = rotate(view, rotation.y, up);
		view = rotate(view, rotation.z, forward);
		view = translate(view, -position); // Negate position so that raw coordinates better align with what's actually being rendered.


		projection = perspective(radians(FieldOfView), float((width * 0.75) / (height * 0.75)), NearClip, FarClip);
	}

	static Camera* main;
};

static void SetMainCamera(Camera& camera)
{
	Camera::main = &camera;
}

void ApplyPerspective(Camera source, ShaderProgram& pro, Transform obj)
{
	pro.UseProgram();
	obj.UpdateMatrices();
	source.UpdateCameraMatrices();

	pro.setMat4("projection", source.projection);
	pro.setMat4("view", source.view);
	pro.setMat4("model", obj.model);
}

class drawable
{
public:
	int order;
	VertexArrayObject vao;
	ShaderProgram program;
	Transform transform;
	BufferObject buffer;
	drawable* db = this;
};

class VertexAttribute
{
public:
	int position, size;
	GLenum type;
	GLboolean normalize;
	int stride;

	VertexAttribute(int position, int size, GLenum type, GLboolean normalize, int stride, int offset = 0)
	{
		this->position = position;
		this->size = size;
		this->type = type;
		this->normalize = normalize;
		this->stride = stride;
		glVertexAttribPointer(position, size, type, normalize, stride, (void*)offset);
		glEnableVertexAttribArray(position);
	}
};

class Texture : public GLObject
{
public:
	void* texData;
	int width, height, MipmapLevel;

	GLenum target, format, imageFormat, datatype;

	Texture()
	{
		glGenTextures(1, &id);
		width = 0;
		height = 0;
		MipmapLevel = 0;
		target = 0;
		format = 0;
		imageFormat = 0;
		datatype = 0;
		texData = nullptr;
	}

	void GenerateTexture(GLenum target, int mipmaplevel, GLenum imageformat, int width, int height, GLenum format, GLenum datatype, void* data, bool makeMipmap = true)
	{
		this->target = target;
		this->MipmapLevel = mipmaplevel;
		this->format = imageformat;
		this->format = format;

		this->height = height;
		this->width = width;

		this->texData = data;



		glBindTexture(target, id);
		glTexImage2D(target, mipmaplevel, imageformat, width, height, 0, format, datatype, data);
		if (makeMipmap) glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(target, 0);
	}

	void Bind(GLenum target)
	{
		glBindTexture(target, id);
	}
};

class Renderer
{
private:
	Renderer(){}

public:
	
	static void Draw(VertexArrayObject& va, ShaderProgram& pro, BufferObject& bo, Transform& wo, bool lit = true)
	{
		va.Bind();
		bo.Bind(bo.buffer);
		pro.UseProgram();
		if (Camera::main == nullptr)
		{
			cout << "Main camera is either unassigned or has been destroyed - cannot draw this object." << endl;
			panic
			return;
		}

		ApplyPerspective(*Camera::main, pro, wo);

		if (lit)
		{
			//pro.setVec3("lightPos")
			for (size_t i = 0; i < Light::Lights.size(); i++)
			{

			}
		}

		glDrawArrays(GL_TRIANGLES, 0, bo.size);
		ResetState();
	}

	static void Draw(drawable d)
	{
		static drawable draws[8192];
		
		if (&draws[d.order] != nullptr)
		{
			if (d.order + 1 < 512) d.order += 1;
		}

		draws[d.order] = d;
		drawable* dptr = &draws[0];
		for (int i = 0; i < 8192; i++)
		{
			if (&draws[i] == nullptr)
			{
				continue;
			}

			Draw(draws[i].vao, draws[i].program, draws[i].buffer, draws[i].transform);
			dptr++;
		}
	}

};

Texture* LoadTexture(string path, GLenum target)
{
	Texture* tex = new Texture();
	int height, width, numChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

	GLenum format = GL_RGB;

	if (!data)
	{
		cout << "Failed to load texture with given path: " << path << endl;
		panic
	}

	if (numChannels == 4) format = GL_RGBA;

	glCall(tex->GenerateTexture(target, 0, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data, true));
	stbi_image_free(data);
	return tex;
}

class Cube : public Transform
{
public:
	VertexArrayObject* VAO = new VertexArrayObject();
	BufferObject* VBO = new BufferObject();
	Shader VertShader = Shader(vertexShaderSource, GL_VERTEX_SHADER), FragShader = Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram = ShaderProgram();
	Texture* texture;
	drawable drawinfo;

	void Initialize(int mode = 0)
	{
		if (mode == 0)
		{
			VertShader.CreateShader();
			VertShader.LinkCodeWithPath(SHADERS_DIRECTORY + string("vertexTextured.glsl"));
			VertShader.Compile();

			FragShader.CreateShader();
			FragShader.LinkCodeWithPath(SHADERS_DIRECTORY + string("fragmentTextured.glsl"));
			FragShader.Compile();

			shaderProgram.InitializeProgram({ VertShader, FragShader });
			shaderProgram.setVec4("color", vec4(1));

			VAO->Generate(1);
			VAO->Bind();

			VBO->Generate(GL_ARRAY_BUFFER);
			VBO->Bind(GL_ARRAY_BUFFER);
			VBO->Copy(GL_ARRAY_BUFFER, PRIMITIVE_CUBE, sizeof(PRIMITIVE_CUBE), GL_STATIC_DRAW);

			texture = LoadTexture(TEXTURES_DIRECTORY + string("dirt.jpg"), GL_TEXTURE_2D);

			VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
			VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (3 * sizeof(float)));

			

			this->scale = onevec;
			PrintErrors();
			ResetState();
		}
		
		if (mode == 1)
		{
			VertShader.CreateShader();
			VertShader.LinkCodeWithPath(SHADERS_DIRECTORY + string("vertexTextured.glsl"));
			VertShader.Compile();

			FragShader.CreateShader();
			FragShader.LinkCodeWithPath(SHADERS_DIRECTORY + string("fragmentTextured.glsl"));
			FragShader.Compile();

			shaderProgram.InitializeProgram({ VertShader, FragShader });
			shaderProgram.setVec4("color", vec4(1));

			VAO->Generate(1);
			VAO->Bind();
			texture = LoadTexture(TEXTURES_DIRECTORY + string("dirt.jpg"), GL_TEXTURE_2D);

			this->scale = onevec;
			PrintErrors();
			ResetState();
		}

		drawinfo.vao = *VAO;
		drawinfo.buffer = *VBO;
		drawinfo.program = shaderProgram;
		drawinfo.transform = *((Transform*)this);
	}

	void Draw(int mode = 0)
	{
		if (mode == 0)
		{
			VBO->Bind(GL_ARRAY_BUFFER);
			shaderProgram.UseProgram();
			VAO->Bind();
		}

		if (mode == 1)
		{
			UpdateDirections();
			texture->Bind(GL_TEXTURE_2D);
			Renderer::Draw(*VAO, shaderProgram, *VBO, *wobj);
		}
	}
};

class Triangle : public Transform
{
public:
	VertexArrayObject* VAO = new VertexArrayObject();
	BufferObject* VBO = new BufferObject();
	Shader VertShader = Shader(vertexShaderSource, GL_VERTEX_SHADER), FragShader = Shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram = ShaderProgram();

	void Initialize(int mode = 0)
	{
		if (mode == 0)
		{
			VertShader.CreateShader();
			VertShader.LinkCode(vertexShaderSource);
			VertShader.Compile();

			FragShader.CreateShader();
			FragShader.LinkCode(fragmentShaderSource);
			FragShader.Compile();

			shaderProgram.InitializeProgram({ VertShader, FragShader });


			float vertices[] = {
				-0.5f, -0.5f, 0.0f, // left  
				0.5f, -0.5f, 0.0f, // right 
				0.0f,  0.5f, 0.0f,
			};


			VAO->Generate(1);
			VAO->Bind();

			VBO->Generate(GL_ARRAY_BUFFER);
			VBO->Bind(GL_ARRAY_BUFFER);
			VBO->Copy(GL_ARRAY_BUFFER, vertices, sizeof(vertices), GL_STATIC_DRAW);

			VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
			
			ResetState();
		}
	}

	void Draw(int mode = 0)
	{
		if (mode == 0)
		{
			VBO->Bind(GL_ARRAY_BUFFER);
			shaderProgram.UseProgram();
			VAO->Bind();
		}

		if (mode == 1)
		{
			UpdateDirections();
			shaderProgram.setVec4("color", vec4(0.4f, 0.9f, 0.1f, 0.5f));
			Renderer::Draw(*VAO, shaderProgram, *VBO, *wobj);
		}
	}
};



vector<Light*> Light::Lights = vector<Light*>();
vector<GLObject> GLObject::objects = vector<GLObject>();
vector<Transform> Transform::ActiveTransforms = vector<Transform>();

Camera* Camera::main = nullptr;
GLFWwindow* window;


float deltaTime = 0, lastFrame = 0;

void UpdateDeltaTime()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void UpdateTransforms()
{
	for (int i = Transform::ActiveTransforms.size() - 1; i >= 0; i--)
	{
		Transform::ActiveTransforms[i].UpdateDirections();
		Transform::ActiveTransforms[i].UpdateMatrices();
	}
}

vector<vec3> get_faces(float query[], int stride = 3)
{
	vec3 vect;
	vector<vec3> ret = vector<vec3>();
	int count;
	for (int i = 0; i < sizeof(query) / sizeof(query[0]); i++)
	{
		if (i % stride == 0)
		{
			i += stride;
			count = 0;
			ret.push_back(vect);
		}
		count++;
		switch (count)
		{
		case 0:
			vect.x = query[i];

		case 1:
			vect.y = query[i];
		case 2:
			vect.z = query[i];
		}
	}
	return ret;
}

#endif