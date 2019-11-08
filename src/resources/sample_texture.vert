#version 300 es

in vec3 position;
in vec3 normal;
in vec2 texcoord0;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec2 textureScale;

out vec3 vWorldPos;
out vec3 vWorldNormal;
out vec2 vTexcoord0;

void main()
{
    gl_Position = projectionMatrix * (viewMatrix * (modelMatrix * vec4(position, 1.0)));
    vTexcoord0 = texcoord0 * textureScale;
}