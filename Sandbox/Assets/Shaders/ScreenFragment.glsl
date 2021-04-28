#version 460 core

out vec4 vFragColor;

in vec2 vUV;

uniform sampler2D uScreenTexture;

void main()
{
    vec3 col = texture(uScreenTexture, vUV).rgb;
    vFragColor = vec4(col, 1.0);
} 