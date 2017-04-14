$input a_position, a_normal, a_texcoord0, a_tangent, a_bitangent
$output v_normal, v_position

#include "bgfx_shader.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
	v_normal = mul(u_modelViewProj, vec4(a_normal, 0.0)).xyz;
	v_position = gl_Position.xyz;
}