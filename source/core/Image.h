//
// Created by voxed on 6/6/22.
//

#ifndef VX_EMBER_IMAGE_H
#define VX_EMBER_IMAGE_H

#include <GL/glew.h>
#include <memory>
#include <span>
#include <vector>

namespace vx::ember {

class Image {
    unsigned short int _width, _height;
    unsigned char* _data;
    GLenum _format;
    GLenum _type;
    size_t _length;

public:
    Image(unsigned short width, unsigned short height, unsigned char* data, GLenum format, GLenum type, size_t length);

    [[nodiscard]] std::span<unsigned char> data() const;
    [[nodiscard]] unsigned short width() const;
    [[nodiscard]] unsigned short height() const;
    [[nodiscard]] GLenum format() const;
    [[nodiscard]] GLenum type() const;
};

}

#endif // VX_EMBER_IMAGE_H
