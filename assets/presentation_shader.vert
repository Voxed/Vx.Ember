#version 440

layout(location = 0) in vec3 POSITION;

out vec2 fTEXCOORD;

void main() {
    gl_Position = vec4(POSITION, 1.0f);

    fTEXCOORD = (POSITION.xy + 1.0f)/2.0f;
}