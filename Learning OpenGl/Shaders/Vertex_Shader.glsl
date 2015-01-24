#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 vUV;

uniform mat4 MVP;
out vec2 UV;

void main(void){
	UV = vUV;
	gl_Position = MVP * vec4(in_position, 1);
}