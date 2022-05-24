#version 440

layout(location = 0) out vec4 cNORMAL;
layout(location = 1) out vec4 cPOS;

in vec3 fNORMAL;
in vec3 fPOS;

void main() {
    cNORMAL = vec4(fNORMAL, 0.0);
    cPOS = vec4(fPOS, 0.0);
}