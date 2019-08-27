#version 410 core
layout(location=0) in vec2 vertexPos;
layout(location=1) in vec2 vertexUV;

out vec2 UV;

uniform int width;
uniform int height;

void main() {
    gl_Position=vec4((vertexPos.x/(width/2))-1, (vertexPos.y/(height/2))-1, 0, 1);

    UV=vertexUV;
}

