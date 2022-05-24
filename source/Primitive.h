//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_PRIMITIVE_H
#define VX_EMBER_PRIMITIVE_H

#include <vector>
#include <glm/glm.hpp>
#include <span>
#include <GL/glew.h>

namespace vx::ember {

    class Program;

    class Primitive {
        std::vector<glm::vec3> _vertices;
        std::vector<glm::vec3> _normals;
        std::vector<unsigned int> _indices;

        GLuint vao;
        GLuint vbo;
        GLuint nbo;
        GLuint ibo;

    public:
        Primitive(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);

        std::span<glm::vec3> vertices();

        std::span<glm::vec3> normals();

        std::span<unsigned int> indices();

        void render(Program& program);
    };

}


#endif //VX_EMBER_PRIMITIVE_H
