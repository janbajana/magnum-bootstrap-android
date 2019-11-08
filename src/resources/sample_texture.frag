uniform mediump vec3 color;
uniform sampler2D srcTex;

in mediump vec2 vTexcoord0;

out mediump vec4 fragmentColor;

void main()
{
    //mediump vec4 srcColor = texture(srcTex, vTexcoord0);
    //fragmentColor = srcColor * vec4(color, 1.0f);
    //fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    fragmentColor.rgb = color*texture(srcTex, vTexcoord0).rgb;
    fragmentColor.a = 1.0;
}