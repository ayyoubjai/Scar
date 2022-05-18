#version 330 core
out vec4 FragColor;
in vec3 fcolor;
<<<<<<< HEAD
in vec2 coord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1,coord) * vec4(fcolor,1.0); 
}
=======

void main()
{
    FragColor = vec4(fcolor,1.0); 
} 
>>>>>>> 3c93d98d08391f8b6763dd81ead632ef6e0fa2a4
