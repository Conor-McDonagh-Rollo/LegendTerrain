#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    // Sample the texture color and its alpha channel
    vec4 texColor = texture(texture1, TexCoord);

    // Set the output color with proper alpha blending
    FragColor = texColor;
}