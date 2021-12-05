#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

uniform mat4 uModel;
uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vUV;

void main()
{
    gl_Position = uViewProjection * uModel * vec4(aPosition, 1.0);
    vColor = aColor;
    vUV = aUV;
}