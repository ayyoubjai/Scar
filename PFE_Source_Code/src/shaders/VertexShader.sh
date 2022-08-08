#version 330 core 

layout (location = 0) in vec3 pos;
out vec3 Pos;
uniform mat4 model;

void main(){
	Pos=pos;
	gl_Position = model * vec4(pos.x,pos.y,pos.z,1.0);
}