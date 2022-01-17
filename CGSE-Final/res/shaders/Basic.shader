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

uniform mat4 u_MVP;

void main(){
	gl_Position = u_MVP * position;
	v_TexCoord = a_texCoord;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;
};


#shader fragment
#version 330 core
//H-Write own Fragment Shader

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_TextureArr[2];

void main(){
	int index = int(v_TexIndex);
	//H-u_Texture stores the pixel positions from the texture, v_TexCoord stores the position of the vertices.
	//As far as i understood, sampler2D also stores the pixelInformation
	color = texture(u_TextureArr[index], v_TexCoord);
	
	//H-Output tex Index as color (Testing)
	//color = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0);
};