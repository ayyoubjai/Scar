#version 330 core
out vec4 FragColor;
in vec3 fcolor;
in vec2 coord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1,coord) * vec4(fcolor,1.0); 
}