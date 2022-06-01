#version 440

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec3 NORMAL;

layout(location = 0) uniform mat4 MODEL_MATRIX;
layout(std140, binding = 0) uniform MatrixBlock {
    mat4 VIEW_MATRIX;
    mat4 PROJECTION_MATRIX;
};

out vec3 fVIEW_NORMAL;
out vec3 fPOS;
out vec3 fVERT_POS;
out vec3 fNORMAL;
out vec3 fVIEW_POS;

void main() {

    float size = 0.5;

    gl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(POSITION*size, 1.0);
    fNORMAL = (inverse(transpose(MODEL_MATRIX)) * vec4(NORMAL, 1.0)).xyz;
    fPOS = (MODEL_MATRIX * vec4(POSITION*size, 1.0)).xyz;
    fVERT_POS = POSITION*size;
    fVIEW_NORMAL = (inverse(transpose(VIEW_MATRIX * MODEL_MATRIX)) * vec4(NORMAL, 1.0)).xyz;
    fVIEW_POS = (VIEW_MATRIX * MODEL_MATRIX * vec4(POSITION*size, 1.0)).xyz;
}