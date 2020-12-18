precision mediump float;
uniform sampler2D mainTex;
//uniform vec4 color;

void main()
{
    gl_FragColor = texture2D(mainTex, gl_PointCoord);
}
