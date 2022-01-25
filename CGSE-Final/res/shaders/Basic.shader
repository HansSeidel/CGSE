#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main(){
	gl_Position = u_Projection * u_View * u_Model * a_position;
	v_TexCoord = a_texCoord;
};


#shader fragment
#version 330 core
//H-Write own Fragment Shader

layout(location = 0) out vec4 o_color;

in vec2 v_TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	o_color = mix(texture(texture1, v_TexCoord), texture(texture2, v_TexCoord), 0.5);
};