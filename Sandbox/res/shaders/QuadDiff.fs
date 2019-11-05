#version 330 core

in vec2 v_TexCoords;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

uniform int u_Texture1Set;
uniform int u_Texture2Set;

out vec4 o_Color;

void main()
{
	vec3 tex1;
	if(u_Texture1Set == 1) tex1 = texture(u_Texture1, v_TexCoords).rgb;
	vec3 tex2; 
	if(u_Texture2Set == 1) tex2 = texture(u_Texture2, v_TexCoords).rgb;
	
	//o_Color = vec4(tex2, 1.0f);
	//o_Color = vec4(tex1, 1.0f);
	o_Color = vec4(abs(tex1 - tex2), 1.0f);
	//o_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}