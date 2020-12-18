precision mediump float;
attribute vec2 vPosition;
attribute vec2 vTextureCoordinates;

uniform mat4 modelViewProjectionMatrix;

varying vec2 textureCoordinates;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(vPosition, 0.0, 1.0);
    textureCoordinates = vTextureCoordinates;
}
