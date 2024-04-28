#version 330
uniform sampler2D myTexture;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {
  fragColor = texture(myTexture, vec2(vsoTexCoord.x, vsoTexCoord.y));
}

#version 330

layout (location = 0) in vec3 vsiPosition;
layout (location = 1) in vec3 vsiNormal;
layout (location = 2) in vec2 vsiTexCoord;
uniform int inv; 
out vec2 vsoTexCoord;

void main(void) {
    gl_Position = vec4(vsiPosition, 1.0);
    if(inv != 0)
        vsoTexCoord = vec2(vsiTexCoord.s, 1.0 - vsiTexCoord.t);
    else
        vsoTexCoord = vec2(vsiTexCoord.s, vsiTexCoord.t);
}