#version 460 core

out vec4 vFragColor;

in vec4 vColor;
in vec2 vUV;

uniform vec4 uColor;
uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;

void main()
{    
	vec4 result = texture(uDiffuse, vUV) + texture(uSpecular, vUV);
	vFragColor = uColor * vColor * result;
}