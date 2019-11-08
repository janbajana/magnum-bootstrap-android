layout(location = 0) uniform mat4 transformationProjectionMatrix;
layout(location = 1) uniform vec2 textureScale;

in mediump vec3 position;
in mediump vec3 normal;
in mediump vec2 texcoord0;

out vec2 vTexcoord0;

void main()
{
    gl_Position = transformationProjectionMatrix*vec4(position, 1.0f);
    vTexcoord0 = texcoord0 * textureScale;
}