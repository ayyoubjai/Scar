#version 330 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 Coord;

out vec2 coord;

void main(){
	coord=Coord;
	gl_Position = vec4(Pos.x,Pos.y,0.0,1.0);
}