#version 440

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec3 NORMAL;
layout(location = 2) in vec2 TEX_COORD;
layout(location = 3) in vec4 TANGENT;

layout(location = 0) uniform mat4 MODEL_MATRIX;
layout(std140, binding = 0) uniform MatrixBlock {
    mat4 VIEW_MATRIX;
    mat4 PROJECTION_MATRIX;
};

out vec3 fNORMAL;
out vec3 fPOS;
out vec2 fTEX_COORD;
out mat3 fTBN;

void main() {
    mat4 NORMAL_MATRIX = inverse(transpose(MODEL_MATRIX));
    vec3 BITANGENT = cross(NORMAL, TANGENT.xyz) * TANGENT.w;

    vec3 WORLDSPACE_TANGENT = normalize((NORMAL_MATRIX * vec4(TANGENT.xyz, 1.0)).xyz);
    vec3 WORLDSPACE_BITANGENT = normalize((NORMAL_MATRIX * vec4(BITANGENT, 1.0)).xyz);
    vec3 WORLDSPACE_NORMAL = normalize((NORMAL_MATRIX * vec4(NORMAL, 1.0)).xyz);
    vec3 WORLDSPACE_POSITION = (MODEL_MATRIX * vec4(POSITION, 1.0)).xyz;

    gl_Position = PROJECTION_MATRIX * VIEW_MATRIX * vec4(WORLDSPACE_POSITION, 1.0);
    fNORMAL = WORLDSPACE_NORMAL;
    fPOS = WORLDSPACE_POSITION;
    fTEX_COORD = TEX_COORD;

    vec3 T = normalize(vec3(NORMAL_MATRIX * vec4(TANGENT.xyz, 1.0)));
    vec3 B = normalize(vec3(NORMAL_MATRIX * vec4(BITANGENT, 1.0)));
    vec3 N = normalize(vec3(NORMAL_MATRIX * vec4(NORMAL, 1.0)));
    fTBN = mat3(T, B, N);
}