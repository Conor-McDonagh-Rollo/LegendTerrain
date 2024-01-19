#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;       // Model matrix uniform
uniform mat4 view;        // View matrix uniform
uniform mat4 projection;  // Projection matrix uniform

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Order matters in matrix multiplication
    TexCoord = aTexCoord;
}