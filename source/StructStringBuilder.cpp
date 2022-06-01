//
// Created by voxed on 5/23/22.
//

#include "StructStringBuilder.h"

std::string vx::ember::StructStringBuilder::build() {
    std::string result;
    result += "(" + std::string(_name) + "){\n";
    for (const auto& field : _fields) {
        result += "\t" + std::string(field.first) + ": " + field.second + ",\n";
    }
    result += "}\n";
    return result;
}
