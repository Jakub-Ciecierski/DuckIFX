#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    color = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.2);
}