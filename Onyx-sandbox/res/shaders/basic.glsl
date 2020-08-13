
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_VertColor;

uniform mat4 u_ViewProjection;

out DATA
{
	vec4 v_Color;
} vs_out;

void main() {
	
	vs_out.v_Color = a_VertColor;	
	
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
layout (location = 0) out vec4 color;

in DATA
{
	vec4 v_Color;

} fs_in;

void main() {

	color = fs_in.v_Color;
	

	
}