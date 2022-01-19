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

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
in vec4 v_Color;

uniform sampler2D u_TextureArr[32];

void main(){
	//H-Calculating +0.5 to correct interpolation errors. (THIS TOOK ME 3 HOURS)
	int index = int(v_TexIndex+0.5);
	//H-u_Texture stores the pixel positions from the texture, v_TexCoord stores the position of the vertices.
	//As far as i understood, sampler2D also stores the pixelInformation
	//The multiply color works the following way: Texture slot 0 is reserved to be a white texture.
	//If a texture is used, the color mus be set to white. This way, it can be determined, which to use. (Texture or Color)
	color = texture(u_TextureArr[index], v_TexCoord) * v_Color;
	
	//H-Output tex Index as color (Testing)
	color = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0);
};