#version 460 core

out vec4 oFragColor;

in vec4 vColor;
in vec2 vTexCoords;

uniform sampler2D uTexture[32];
uniform int uTexIndex;

void main()
{
	oFragColor = vColor * texture(uTexture[uTexIndex], vTexCoords);
}