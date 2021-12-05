#version 460 core

out vec4 vFragColor;

in vec4 vColor;
in vec2 vUV;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{    
	vFragColor = uColor * vColor * texture(uTexture, vUV);
}