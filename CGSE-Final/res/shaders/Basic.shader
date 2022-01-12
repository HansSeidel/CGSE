#shader vertex
#version 330 core
//H-Write own Vertex Shader

layout(location = 0) in vec4 position;
layout(location = 1) in vec2  texCoord;

out vec2 v_TexCoord;

void main(){
	gl_Position = position;
	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core
//H-Write own Fragment Shader

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
	//H-u_Texture stores the pixel positions from the texture, v_TexCoord stores the position of the vertices.
	//As far as i understood, sampler2D also stores the pixelInformation
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};