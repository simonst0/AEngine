precision mediump float;
varying vec2 textureCoordinates;
uniform sampler2D mainTex;
uniform vec4 color;
uniform int useTex;

void main()
{
    vec4 OutColor = vec4(0,0,0,0);
    if(useTex > 0)
        OutColor = color * texture2D(mainTex, textureCoordinates);
    else
        OutColor = color;
    gl_FragColor = OutColor;
}
