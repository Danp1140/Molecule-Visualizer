#version 410 core

in vec3 fragmentPos;
in vec3 normals;

uniform vec3 tint;
uniform vec3 viewPos;
uniform float shininess;

out vec4 color;

void main() {
    //reworks with lighting?
    //make objects gradually transparent as they come closer to the camera
    vec3 lightColor=vec3(1,1,1);
    vec3 lightPos=viewPos-vec3(5, 0, 10);
    vec3 ambientLightColor=vec3(0.2f, 0.2f, 0.2f);

    vec3 lightDirection=normalize(lightPos-fragmentPos);
    //vec3 viewDirection=normalize(viewPos-fragmentPos);
    //vec3 halfwayDirection=normalize(lightDirection+viewDirection);
    vec3 specularColor=(pow(max(dot(normals, lightDirection), 0.0), shininess)*lightColor)+ambientLightColor;

//    vec3 halfwayDirection=normalize(normalize(lightPos-fragmentPos)+normalize(viewPos-fragmentPos));
//    vec3 specularColor=pow(max(dot(normals, halfwayDirection), 0.0), shininess)*lightColor;


    vec4 outcolor=vec4(tint, 1.0f)*vec4(specularColor, 1.0f);
    float distance=sqrt(pow(fragmentPos.x-viewPos.x, 2)+pow(fragmentPos.y-viewPos.y, 2)+pow(fragmentPos.z-viewPos.z, 2));
    if(distance<3){outcolor.a=distance/3;}
    color=outcolor;
}
