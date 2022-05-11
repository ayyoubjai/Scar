#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
uniform vec2 ucolor;
out vec3 fcolor;

void main(){
	gl_Position = vec4(Pos, 1.0);
	fcolor=Color+vec3(ucolor,0);
}
