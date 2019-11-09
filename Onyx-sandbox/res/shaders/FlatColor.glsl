
#type vertex
#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform vec3 u_VertexColor;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out DATA
{
	vec4 position;
	vec4 color;
} vs_out;

void main() {

	gl_Position = u_ViewProjection * u_Transform * vec4(vertexPosition_modelspace, 1);
	vs_out.position =  u_ViewProjection * u_Transform *vec4(vertexPosition_modelspace, 1);
	vs_out.color = vec4(u_VertexColor, 1);
}

#type fragment
#version 330 core
layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main() {

	color = fs_in.color; 

}