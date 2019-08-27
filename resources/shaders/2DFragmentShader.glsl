#version 410 core

in vec2 UV;

out vec4 color;

uniform sampler2D texSampler;
uniform vec4 inColor;
uniform int type;
//type 0=color
//type 1=texture
//type 2=text

void main() {
    vec4 temp;
    if(type==0){temp=inColor;}
    else if(type==1){temp=texture(texSampler, UV)*inColor;}
    else if(type==2){temp=(vec4(1, 1, 1, 1)*vec4(1, 1, 1, texture(texSampler, UV).r))*inColor;}
    color=temp;
}
