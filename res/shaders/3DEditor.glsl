
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_VertColor;
layout(location = 2) in vec4 a_EntityIdentifier;

uniform mat4 u_ViewProjection;

out DATA
{
	vec3 v_Position;
	vec4 v_Color;
	vec4 v_EntityIdentifier;
} vs_out;

void main() {
	
	vs_out.v_Color = a_VertColor;	
	vs_out.v_Position =  a_Position;
	vs_out.v_EntityIdentifier = a_EntityIdentifier;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

}

#type fragment
#version 330 core
layout (location = 0) out vec4 color;
layout (location = 1) out vec4 entityIdentifier;

uniform vec3 u_LightPosition;

in DATA
{
	vec3 v_Position;
	vec4 v_Color;
	vec4 v_EntityIdentifier;

} fs_in;

void main() {

	float intensity = 10.0;
	color = fs_in.v_Color;
	entityIdentifier = fs_in.v_EntityIdentifier;
	
}