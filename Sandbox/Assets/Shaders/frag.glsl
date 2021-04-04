#version 460 core

out vec4 oFragColor;
in vec3 oColor;
in vec2 oTexCoords;

uniform sampler2D uTexture1;
//uniform vec4 uColor;

void main()
{
	oFragColor = texture(uTexture1, oTexCoords);
}