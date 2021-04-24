#version 460 core

out vec4 oFragColor;

in vec2 vUV;

uniform sampler2D uScreenTexture;

void main()
{
    vec3 col = texture(uScreenTexture, vUV).rgb;
    oFragColor = vec4(col, 1.0);
} 