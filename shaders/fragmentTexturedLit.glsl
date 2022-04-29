#version 330 core
out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;

in vec2 TextureCoordinates;

uniform vec3 lightPos, lightColor;
uniform float lightRange, lightIntensity, lightSpecint;
uniform bool lightShadows;

void main()
{
	
	FragColor = texture(tex, TextureCoordinates) * color;
}