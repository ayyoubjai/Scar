#version 330 core 
in vec3 Pos;
out vec4 FColor;
uniform vec4 Color;
void main(){
	if(length(Pos)>0.175){
		discard;
	}
	FColor=vec4(Color.x,Color.y,Color.z,Color.w);
}