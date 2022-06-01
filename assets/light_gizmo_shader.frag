#version 440

layout(location = 0) out vec4 COLOR;

layout(binding = 0) uniform samplerCube CUBE_MAP;
layout(binding = 1) uniform sampler2D OCCLUSION_MAP;

layout(location = 1) uniform vec2 WINDOW_SIZE;


in vec3 fVIEW_NORMAL;
in vec3 fPOS;
in vec3 fVERT_POS;
in vec3 fNORMAL;
in vec3 fVIEW_POS;

void main() {
    float fres = dot(fVIEW_NORMAL, normalize(-fVIEW_POS));
    COLOR = mix(texture(CUBE_MAP, normalize(fNORMAL)), vec4(1.0), 0.25 - fres/4.0);
    COLOR.a = 1.0;

    if (fres < 0.4)
    COLOR = vec4(1.0);

    if (gl_FragCoord.z > texture(OCCLUSION_MAP, gl_FragCoord.xy/WINDOW_SIZE).x)
    discard;

}