#shader vertex
#version 330 core
//H-Write own Vertex Shader

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;

out vec2 v_TexCoord;
out float v_TexIndex;
out vec4 v_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main(){
	gl_Position = u_Model * u_View * u_Projection * position;
	v_TexCoord = a_texCoord;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;
};


#shader fragment
#version 330 core
//H-Write own Fragment Shader

layout(location = 0) out vec4 o_color;

in vec2 v_TexCoord;
in float v_TexIndex;
in vec4 v_Color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	o_color = mix(texture(texture1, v_TexCoord), texture(texture2, v_TexCoord), 0.5);
};