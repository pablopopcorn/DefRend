#version 330

layout(location = 0) in vec3 inPosition;

uniform mat4 worldViewProjectionMatrix;

void main()
{
	gl_Position = worldViewProjectionMatrix * vec4(inPosition, 1.0);
}