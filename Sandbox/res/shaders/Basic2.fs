#version 330 core

//in vec2 v_TexCoords;

uniform sampler2D u_Texture;

uniform mat4 V;
uniform mat4 P;
uniform mat4 VP;


layout(location = 0) out vec4 o_Color;

void main()
{
	//vec4 col = texture(u_Texture, v_TexCoords);
	o_Color = vec4(0.75f, 0.2f, 0.15f, 1.0f);
}