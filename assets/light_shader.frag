#version 440

layout(location = 0) out vec4 COLOR;

layout(binding = 0) uniform sampler2DMS POS_MAP;
layout(binding = 1) uniform sampler2DMS NORM_MAP;
layout(binding = 2) uniform sampler2DMS METALLIC_MAP;
layout(binding = 3) uniform sampler2DMS COLOR_MAP;
layout(binding = 4) uniform samplerCubeShadow LIGHT_POS_CUBE_MAP;

layout(location = 0) uniform vec3 LIGHT_POS;
layout(location = 1) uniform vec3 CAM_POS;


layout(std140, binding = 1) uniform LightBlock {
    vec4 LIGHT_COLOR;
    float INTENSITY;
};


in vec2 fTEXCOORD;



ivec2 texCoords(sampler2DMS sampler, vec2 uv)
{
    ivec2 texSize = textureSize(sampler);
    ivec2 texCoord = ivec2(uv * texSize);

    return texCoord;
}

ivec3 texCoords(sampler2DMSArray sampler, vec3 uv)
{
    ivec3 texSize = textureSize(sampler);
    ivec3 texCoord = ivec3(uv * texSize);

    return texCoord;
}

vec4 textureMultisample(sampler2DMSArray sampler, vec3 uv) {
    float sampleCount = 8.0;
    vec4 color = vec4(0);

    for (int i = 0; i < sampleCount; i++) {
        color += texelFetch(sampler, texCoords(sampler, uv), i);
    }

    return color / sampleCount;
}

vec4 textureMultisample(sampler2DMS sampler, vec2 uv) {
    float sampleCount = 8.0;
    vec4 color = vec4(0);

    for (int i = 0; i < sampleCount; i++) {
        color += clamp(vec4(0.0), vec4(1.0), texelFetch(sampler, texCoords(sampler, uv), i));
    }

    return color / sampleCount;
}


void main() {

    vec3 norm = texelFetch(NORM_MAP, texCoords(NORM_MAP, fTEXCOORD), gl_SampleID).xyz;
    vec4 pos = texelFetch(POS_MAP, texCoords(POS_MAP, fTEXCOORD), gl_SampleID);
    if (dot(norm, normalize(LIGHT_POS - pos.xyz)) <= 0) {
        COLOR = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec3 metal = texelFetch(METALLIC_MAP, texCoords(METALLIC_MAP, fTEXCOORD), gl_SampleID).xyz;
    vec3 color = texelFetch(COLOR_MAP, texCoords(COLOR_MAP, fTEXCOORD), gl_SampleID).xyz;

    float metallic = metal.r;
    float roughness = metal.g;

    float distance = length(pos.xyz - LIGHT_POS);

    vec3 wi = normalize(LIGHT_POS - pos.xyz);
    vec3 wo = normalize(CAM_POS - pos.xyz);

    float bias = max(0.1 * (1.0 - dot(norm, wi)), 0.005);

    float shadow = texture(LIGHT_POS_CUBE_MAP, vec4(normalize(pos.xyz - LIGHT_POS), (distance - bias)/10.0)).x;

    vec3 li = LIGHT_COLOR.rgb * INTENSITY * 1/pow(distance, 2);

    //float lightDistance = length(lightPos - LIGHT_POS);
    vec3 diff = max(vec3(0), vec3(color*(1.0/3.14)*dot(norm, normalize(LIGHT_POS - pos.xyz))*li));

    float PI = 3.14;

    vec3 h = normalize(wi + wo);
    vec3 n = norm;
    float cosTheta = dot(n, h);

    float ndfGGXTR = pow(roughness, 2.)/(PI*pow(pow(dot(n, h), 2.)*(pow(roughness, 2.) - 1.) + 1.0, 2.0));

    vec3 F0 = vec3(0.04);
    F0      = mix(F0, color, metallic);

    vec3 Fschlick = F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);



    float k = pow(roughness + 1.0, 2.0)/8.0;





    float NdotV = max(dot(n, wo), 0.0);
    float NdotO = max(dot(n, wi), 0.0);

    float DschlickGGX = (NdotV/(NdotV*(1 - k) + k)) *  (NdotO/(NdotO*(1 - k) + k));




    vec3 fCookTorrence = (DschlickGGX * Fschlick * ndfGGXTR) / (4 * dot(wo, n)*dot(wi, n));

    COLOR = vec4(shadow * vec3((roughness)*(color/3.14) + (1 - roughness)*fCookTorrence)* li * dot(n, wi), 1.0);
    //COLOR = vec4(diff*shadow, 0.0);
    //COLOR = vec4(metallic, 0.0, 0.0, 1.0);
}