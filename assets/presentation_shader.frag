#version 440

layout(location = 0) uniform int CUBE_MAP;
layout(location = 1) uniform int FACE;
layout(location = 2) uniform int GIZMOS;

layout(location = 0) out vec4 COLOR;
layout(binding = 0) uniform sampler2D TEXTURE;
layout(binding = 1) uniform samplerCube TEXTURE_CUBEMAP;

layout(binding = 2) uniform sampler2D GIZMO_OVERLAY;

in vec2 fTEXCOORD;

void main() {
    if (CUBE_MAP == 0) {
        COLOR = texture(TEXTURE, fTEXCOORD);
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
        vec4 gColor = texture(GIZMO_OVERLAY, fTEXCOORD);
        COLOR = vec4((COLOR*(1.0-gColor.a) + gColor*gColor.a).xyz, 1.0);
    }
}