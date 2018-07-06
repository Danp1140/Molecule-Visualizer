#version 410 core

layout(location=0) in vec3 vertexPosition_modelspace;
layout(location=1) in vec3 vertexNormals;

uniform mat4 M;
uniform mat4 VP;

out vec3 fragmentPos;
out vec3 normals;

void main() {
    gl_Position=VP*M*vec4(vertexPosition_modelspace,1);
    fragmentPos=vec3(M*vec4(vertexPosition_modelspace,1));
    normals=mat3(transpose(inverse(M)))*vertexNormals;
}
