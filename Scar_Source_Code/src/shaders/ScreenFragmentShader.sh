#version 330 core

in vec2 coord;

out vec4 Color;

uniform sampler2D tex;

void main(){
	Color=texture(tex,coord);
}