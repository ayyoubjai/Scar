#version 330 core 
in vec3 Pos;
out vec4 Color;
void main(){
	if(length(Pos)>0.125){
		discard;
	}
	Color=vec4(0.0, 0.0, 1.0, 1.0);
}