#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

//uniform mat4 pr_matrix = mat4(1.0);
//uniform mat4 vw_matrix = mat4(1.0);
//uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec3 color;
} vs_out;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = pr_matrix * vw_matrix * (ml_matrix * vec4(vertexPosition_modelspace, 1));

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	vs_out.position =  vec4(vertexPosition_modelspace, 1);
	vs_out.color = vertexColor;
}