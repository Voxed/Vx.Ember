#version 440

layout(location = 0) uniform int CUBE_MAP;
layout(location = 1) uniform int FACE;
layout(location = 2) uniform int GIZMOS;
layout(location = 3) uniform int ARRAY;
layout(location = 4) uniform int ELEMENT;

layout(location = 5) uniform int MIX_ARRAY;
layout(location = 6) uniform int MIX_ARRAY_SIZE;

layout(location = 0) out vec4 COLOR;
layout(binding = 0) uniform sampler2DMS TEXTURE;
layout(binding = 1) uniform samplerCube TEXTURE_CUBEMAP;

layout(binding = 2) uniform sampler2D GIZMO_OVERLAY;
layout(binding = 3) uniform sampler2DMSArray TEXTURE_ARRAY;

in vec2 fTEXCOORD;


ivec2 texCoords(sampler2DMS sampler, vec2 uv)
{
    ivec2 texSize = textureSize(sampler);
    ivec2 texCoord = ivec2(uv * texSize);

    return texCoord;
}

ivec2 texCoords(sampler2D sampler, vec2 uv)
{
    ivec2 texSize = textureSize(sampler, 0);
    ivec2 texCoord = ivec2(uv * texSize);

    return texCoord;
}

ivec3 texCoords(sampler2DMSArray sampler, vec3 uv)
{
    ivec3 texSize = textureSize(sampler);
    ivec3 texCoord = ivec3(uv.xy * texSize.xy, int(uv.z));

    return texCoord;
}

vec4 textureMultisample(sampler2DMSArray sampler, vec3 uv) {
    float sampleCount = 8.0;
    vec4 color = vec4(0);

    for (int i = 0; i < sampleCount; i++) {
        color += clamp(vec4(0.0), vec4(1.0), texelFetch(sampler, texCoords(sampler, uv), i));
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
    if (ARRAY != 0) {
        if (MIX_ARRAY != 0) {
            for (int i = 0; i < MIX_ARRAY_SIZE; i++) {
                COLOR += textureMultisample(TEXTURE_ARRAY, vec3(fTEXCOORD, float(i)));
            }
            //COLOR /= float(MIX_ARRAY_SIZE);
        } else {
            COLOR = textureMultisample(TEXTURE_ARRAY, vec3(fTEXCOORD, float(ELEMENT)));
        }
        //COLOR = vec4(1.0, 0.0, 0.0, 1.0);
    } else if (CUBE_MAP == 0) {
        COLOR = textureMultisample(TEXTURE, fTEXCOORD);
    } else {

        vec3 uv = vec3(fTEXCOORD*2.0 - 1.0, 1.0);

        switch (FACE) {
            case 0:
            uv = vec3(1.0, uv.y, uv.x);
            break;
            case 1:
            uv = vec3(-1.0, uv.y, -uv.x);
            break;
            case 2:
            uv = vec3(uv.x, 1.0, uv.y);
            break;
            case 3:
            uv = vec3(uv.x, -1.0, -uv.y);
            break;
            case 4:
            uv = vec3(-uv.x, uv.y, 1.0);
            break;
            case 5:
            uv = vec3(uv.x, uv.y, -1.0);
            break;
        };
        COLOR = texture(TEXTURE_CUBEMAP, normalize(uv));
    }

    COLOR = clamp(vec4(0), vec4(1), COLOR);

    if (GIZMOS == 1) {
        vec4 gColor = texelFetch(GIZMO_OVERLAY, texCoords(GIZMO_OVERLAY, fTEXCOORD), 0);
        COLOR = vec4((COLOR*(1.0-gColor.a) + gColor*gColor.a).xyz, 1.0);
    }
}