#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBitangent;

out vec3 vFragPosition;
out vec3 vNormal;
out vec2 vUV;

uniform mat4 uModel;
uniform mat4 uViewProjection;

void main()
{
    vFragPosition = vec3(uModel * vec4(aPosition, 1.0));
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;  
    vUV = aUV;
    
    gl_Position = uViewProjection * vec4(vFragPosition, 1.0);
}