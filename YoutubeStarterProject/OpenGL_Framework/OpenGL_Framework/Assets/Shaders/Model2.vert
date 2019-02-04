#version 420

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
in vec3 in_vert;
in vec2 in_uv;
in vec3 in_normal;


out vec3 out_vert;
out vec3 normal;
out vec2 texcoord;
void main()
{
	vec3 _vert = in_vert;
	gl_Position = uProj * uView * uModel * vec4(_vert,1.0);
	texcoord = in_uv;
	//normal = in_normal;
	out_vert = _vert;
}