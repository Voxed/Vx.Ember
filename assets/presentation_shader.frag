#version 440

layout(location = 0) out vec4 COLOR;
layout(binding = 0) uniform sampler2D TEXTURE;

in vec2 fTEXCOORD;

void main() {
    COLOR = texture(TEXTURE, fTEXCOORD);
}