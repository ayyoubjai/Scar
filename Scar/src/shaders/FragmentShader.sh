#version 330 core
out vec4 FragColor;
in vec3 fcolor;
in vec2 tcoord;

uniform sampler2D text1;



void main()
{
    FragColor = texture(text1,tcoord) * vec4(fcolor,1.0); 
}