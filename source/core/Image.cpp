//
// Created by voxed on 6/6/22.
//

#include "Image.h"

#include <utility>

using namespace vx::ember;

Image::Image(
    unsigned short width, unsigned short height, unsigned char* data, GLenum format, GLenum type, size_t length)
    : _height(height)
    , _width(width)
    , _data(data)
    , _format(format)
    , _type(type)
    , _length(length) { }

std::span<unsigned char> Image::data() const { return std::span<unsigned char>(_data, _length); }

unsigned short Image::width() const { return _width; }

unsigned short Image::height() const { return _height; }

GLenum Image::format() const { return _format; }

GLenum Image::type() const { return _type; }
