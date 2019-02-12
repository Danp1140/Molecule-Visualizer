#version 410 core
layout(location=0) in vec3 vertpos;

void main() {
//    vec2 newvertpos=vertpos-vec2(400, 300);
//    newvertpos/=vec2(400, 300);
//    gl_Position=vec4(newvertpos, 0.0, 1.0);
    gl_Position=vec4(vertpos, 1);
}

