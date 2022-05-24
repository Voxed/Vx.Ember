#version 440

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec3 NORMAL;

layout(location = 0) uniform mat4 MODEL_MATRIX;
layout(location = 1) uniform mat4 VIEW_MATRIX;
layout(location = 2) uniform mat4 PROJECTION_MATRIX;

out vec3 fNORMAL;
out vec3 fPOS;

void main() {
    gl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(POSITION, 1.0);
    fNORMAL = (inverse(transpose(MODEL_MATRIX)) * vec4(NORMAL, 1.0)).xyz;
    fPOS = (MODEL_MATRIX * vec4(POSITION, 1.0)).xyz;
}