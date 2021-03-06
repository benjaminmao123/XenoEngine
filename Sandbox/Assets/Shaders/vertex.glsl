#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBiTangent;

uniform mat4 uMVP;

out vec4 vColor;
out vec2 vUV;

void main()
{
	gl_Position = uMVP * vec4(aPosition, 1.0);
	vColor = aColor;
	vUV = aUV;
}