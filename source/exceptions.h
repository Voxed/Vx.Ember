//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_EXCEPTIONS_H
#define VX_EMBER_EXCEPTIONS_H

#include <exception>
#include <filesystem>
#include <utility>

namespace vx::ember {

class Exception : public std::exception {
    std::string _what;

public:
    explicit Exception(std::string what)
        : _what(std::move(what)) { }

    [[nodiscard]] const char* what() const noexcept override {
        return _what.c_str();
    }
};

class FileNotFoundException : public Exception {
public:
    explicit FileNotFoundException(const std::filesystem::path& file)
        : Exception("File \"" + file.generic_string() + "\" does not exist!") {
    }
};

class InvalidModelException : public Exception {
public:
    explicit InvalidModelException(
        const std::filesystem::path& file, const std::string& reason)
        : Exception(
            "Model \"" + file.generic_string() + "\" is invalid! " + reason) { }
};

class ShaderCompileException : public Exception {
public:
    explicit ShaderCompileException(const std::string& shaderType,
        const std::string& shaderName, const std::string& infoLog)
        : Exception(shaderType + " shader \"" + shaderName
            + "\" failed to compile. Info log: \n" + infoLog) { }
};

}

#endif // VX_EMBER_EXCEPTIONS_H
