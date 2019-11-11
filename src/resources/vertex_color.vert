layout(location = 0) uniform mat4 transformationProjectionMatrix;

in highp vec3 position;
in mediump vec3 normal;
in lowp vec3 color;

out lowp vec3 vInterpolatedColor;
out lowp vec3 vNormal;

void main() {
    gl_Position = transformationProjectionMatrix*vec4(position, 1.0f);
    vInterpolatedColor = color;
    vNormal = (transformationProjectionMatrix * vec4(normal.xyz, 0.0)).xyz;
}