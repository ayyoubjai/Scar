#version 330 core 

in vec3 Pos;
out vec4 FColor;
uniform vec4 Color;
void main(){
	FColor=vec4(Color.x,Color.y,Color.z,Color.w);
}