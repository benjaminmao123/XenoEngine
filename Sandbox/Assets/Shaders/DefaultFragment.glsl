#version 460 core

out vec4 oFragColor;

in vec4 vColor;
in vec2 vUV;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
	oFragColor = uColor * vColor * texture(uTexture, vUV);
}