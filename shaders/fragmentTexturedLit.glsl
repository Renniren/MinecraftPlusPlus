#version 330 core
out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;

in vec2 TextureCoordinates;

struct Light
{
	vec3 pos, color;
	float range, intensity, specularIntensity;
	bool useShadows;
};

uniform Light lights[512];

void main()
{
	
	FragColor = texture(tex, TextureCoordinates) * color;
}