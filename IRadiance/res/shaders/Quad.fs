#version 330 core

layout (location = 1) in vec2 v_TexCoords;

uniform sampler2D u_Texture;

out vec4 o_Color;

void main()
{
	o_Color = texture(u_Texture, v_TexCoords);
}