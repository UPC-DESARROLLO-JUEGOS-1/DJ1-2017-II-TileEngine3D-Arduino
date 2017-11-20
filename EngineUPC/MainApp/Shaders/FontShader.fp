#version 130

in vec2 fragmentUV;
in vec4 fragmentColor;

out vec4 color;

uniform sampler2D sampler;

void main()
{
	color = (texture(sampler, fragmentUV))* fragmentColor;
}