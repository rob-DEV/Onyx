#type vertex
#version 450 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_VertColor;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in vec3 a_Tangent;

uniform mat4 u_ViewProjection;
uniform vec3 u_LightPosition;

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

	float intensity = 3.0f / length(fs_in.v_Position.xyz - u_LightPosition.xyz);
	color = vec4(1.0,0.0,0.0,1.0) * vec4(intensity, intensity, intensity, 1.0f);
	
}