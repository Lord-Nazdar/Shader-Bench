$input v_normal, v_position

#include "bgfx_shader.sh"

const vec3 lightPos = vec3(-10.0,10.0,-10.0);
const vec3 ambient = vec3(0.9,1.0,1.0);
const vec3 lightColor = vec3(0.0,1.0,0.5);
const float lightPower = 0.8;

SAMPLER2D(s_texNormal, 0);

void main() {
	vec3 l = normalize(lightPos - v_position);
	float distance = length(l);
	distance = distance * distance;
	float dot_l_n = dot(l, normalize(v_normal));
	
  gl_FragColor = vec4(dot_l_n,dot_l_n,0.0, 1.0);
}