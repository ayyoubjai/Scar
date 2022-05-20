#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 Coord;

out vec3 fcolor;
out vec2 tcoord;

uniform vec2 ucolor;
uniform mat4 model;

void main(){
	gl_Position = model * vec4(Pos, 1.0);
	fcolor=Color+vec3(ucolor,0);
	tcoord=Coord;
}
