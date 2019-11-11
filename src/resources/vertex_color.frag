in lowp vec3 vInterpolatedColor;
in lowp vec3 vNormal;

out lowp vec4 fragmentColor;

void main() {
    fragmentColor = vec4(vInterpolatedColor, 1.0f);
    //fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}