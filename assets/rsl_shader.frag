#version 440

/*layout(location = 0) out vec4 cNORMAL;
layout(location = 1) out vec4 cPOS;
layout(location = 2) out vec4 cCOLOR;
layout(location = 3) out vec4 cMETALLIC_ROUGHNESS;
layout(location = 4) out vec4 cEMISSION;
*/

in vec3 fNORMAL;
in vec3 fPOS;
in vec2 fTEX_COORD;
in mat3 fTBN;

layout(location = 1) uniform vec3 LIGHT_POS;

layout(std140, binding = 1) uniform MaterialUniformBlock {
    vec4 BASE_COLOR;
    vec4 EMISSION;
    float METALLIC;
    float ROUGHNESS;
    float NORMAL_MAP_SCALE;
    uint HAS_BASE_TEXTURE;
    uint HAS_METALLIC_ROUGHNESS_TEXTURE;
    uint HAS_NORMAL_MAP_TEXTURE;
    uint HAS_EMISSION_MAP_TEXTURE;
};
layout(binding = 2) uniform sampler2D baseColorTexture;


layout(binding = 0) uniform sampler2D normalMapTexture;
layout(binding = 1) uniform sampler2D emissionMapTexture;
layout(binding = 3) uniform sampler2D metallicRoughnessTexture;

void main() {
    vec4 cCOLOR;
    if (HAS_BASE_TEXTURE == 1) {
        cCOLOR = texture(baseColorTexture, fTEX_COORD) * BASE_COLOR;
    } else {
        cCOLOR = BASE_COLOR;
    }
    if (cCOLOR.a == 0)
    discard;
    /*if (HAS_NORMAL_MAP_TEXTURE == 1) {
        vec3 normal = texture(normalMapTexture, fTEX_COORD).rgb;
        normal = normal * 2.0 - 1.0;
        normal = normalize(fTBN * normal);
        cNORMAL = vec4(mix(fNORMAL, normal, NORMAL_MAP_SCALE), 1.0);
    } else {
        cNORMAL = vec4(fNORMAL, 1.0);
    }
    if (HAS_EMISSION_MAP_TEXTURE == 1) {
        cEMISSION = vec4(texture(emissionMapTexture, fTEX_COORD).xyz * EMISSION.xyz, 1.0);
    } else {
        cEMISSION = vec4(EMISSION.xyz, 1.0);
    }
    if (HAS_METALLIC_ROUGHNESS_TEXTURE == 1){
        vec2 mr = vec2(METALLIC, ROUGHNESS);
        cMETALLIC_ROUGHNESS = vec4(texture(metallicRoughnessTexture, fTEX_COORD).bg * mr, 0.0, 1.0);
    } else {
        cMETALLIC_ROUGHNESS = vec4(METALLIC, ROUGHNESS, 0.0, 1.0);
    }
    cPOS = vec4(fPOS, 1.0);*/
    gl_FragDepth = length(LIGHT_POS - fPOS)/10.0;
}