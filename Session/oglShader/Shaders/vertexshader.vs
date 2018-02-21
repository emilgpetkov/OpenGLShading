#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

out vec3 FragPos;
out vec3 v3Color;
out vec3 v3Normal;

void main ()
{
	FragPos = vec3(mModel * vec4(vPos, 1.0));
	v3Normal = vNormal;
	v3Color = v3Normal;
	gl_Position = mProjection * mView * vec4(FragPos, 1.0);
}


