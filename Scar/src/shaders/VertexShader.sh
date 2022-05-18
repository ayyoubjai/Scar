#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
<<<<<<< HEAD
layout (location = 2) in vec2 Coord;

out vec3 fcolor;
out vec2 coord;
uniform vec2 ucolor;

=======
uniform vec2 ucolor;
out vec3 fcolor;
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4

void main(){
	gl_Position = vec4(Pos, 1.0);
	fcolor=Color+vec3(ucolor,0);
<<<<<<< HEAD
	coord=Coord;
=======
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
}
