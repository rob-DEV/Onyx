
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_VertColor;

uniform mat4 u_ViewProjection;

out DATA
{
	vec4 v_Color;
	vec3 v_Position;
} vs_out;

void main() {
	
	vs_out.v_Color = a_VertColor;	
	vs_out.v_Position =  a_Position;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

}

#type fragment
#version 330 core
layout (location = 0) out vec4 color;

uniform vec3 u_LightPosition;

in DATA
{
	vec4 v_Color;
	vec3 v_Position;

} fs_in;

void main() {

	float intensity = 5.0f / length(fs_in.v_Position.xyz - u_LightPosition.xyz);
	color = fs_in.v_Color * intensity * vec4(1.0,1.0,1.0,99999999999.0);
	

	
}