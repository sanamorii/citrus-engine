#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec4 colour;
uniform sampler2D ourTexture;

void main(){
	//FragColor = vec4(ourColor, 1);
	FragColor = texture(ourTexture, TexCoord);
}