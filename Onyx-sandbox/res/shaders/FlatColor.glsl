
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;


uniform vec3 u_VertexColor;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out DATA
{
	vec4 position;
	vec4 color;
	vec2 v_TexCoord;
} vs_out;

void main() {

	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
	vs_out.position =  u_ViewProjection * u_Transform *vec4(a_Position, 1);
	vs_out.color = vec4(u_VertexColor, 1);
	vs_out.v_TexCoord = a_TextureCoord;
}

#type fragment
#version 330 core
layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 v_TexCoord;
} fs_in;

uniform sampler2D u_Texture;

void main() {

	color = texture(u_Texture, fs_in.v_TexCoord * 1.0) * fs_in.color;
	//color = fs_in.color; 

}