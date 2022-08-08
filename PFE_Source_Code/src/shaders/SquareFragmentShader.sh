#version 330 core

in vec2 Coord;
in vec3 Pos;
out vec4 FColor;

uniform sampler2D tex;

void main(){
	FColor=texture(tex,Coord);
}