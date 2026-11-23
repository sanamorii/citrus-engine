#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 lightColour;
uniform vec3 objectColour;

void main(){
	//FragColor = vec4(ourColor, 1);
	FragColor = vec4(1.0);
}