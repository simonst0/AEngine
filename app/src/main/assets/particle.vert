precision mediump float;
attribute vec2 vPosition;
attribute float vSize;
uniform mat4 modelViewProjectionMatrix;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(vPosition, 0.0, 1.0);
    gl_PointSize = vSize;
}
