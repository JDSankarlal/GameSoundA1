#version 420

layout (binding = 1)uniform sampler2D grassTex;
layout (binding = 2)uniform sampler2D rockTex;
layout (binding = 4)uniform sampler2D sandTex;

vec4 texel0,texel1,texel2,texel3;


out vec4 outColor;
in vec3 out_vert;
in vec3 normal;
in vec2 texcoord;

void main()
{
	outColor = vec4(1, 0, 1, 1);
}
