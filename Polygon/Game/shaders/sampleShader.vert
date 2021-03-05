#version 330 core

uniform mat4 viewProj;
uniform mat4 transform;
uniform vec3 objectPosition;

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 normalDir;
layout (location = 2) in vec2 textureCoords;

out vec3 normalWolrdDirection;
out vec3 fragPos;
out vec2 textCoords;

void main(){
	
	gl_Position = viewProj * transform * vec4(vertexPos, 1);

	fragPos = vec3(transform * vec4(vertexPos, 1.0));
	normalWolrdDirection = mat3(transpose(inverse(transform))) * normalDir;

	textCoords = textureCoords;
}