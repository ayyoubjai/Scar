#version 330 core 

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 coord;

out vec3 Pos;
out vec2 Coord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main(){
	Pos=pos;
	Coord=coord;
	gl_Position = model * vec4(pos.x,pos.y,pos.z,1.0);
}