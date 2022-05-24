//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_STRUCTSTRINGBUILDER_H
#define VX_EMBER_STRUCTSTRINGBUILDER_H


#include <map>
#include <string>

namespace vx::ember {

    class StructStringBuilder {
        std::map<const char*, std::string> _fields;
        const char* _name;
    public:
        explicit StructStringBuilder(const char* name) : _name(name) {};

        // Objects
        template<typename T> requires (!std::is_arithmetic_v<T>)
        StructStringBuilder addField(const char* fieldName, T& fieldValue) {
            _fields[fieldName] = static_cast<std::string>(fieldValue);

            return std::move(*this);
        }

        // Booleans
        template<typename T> requires (std::same_as<T, bool>)
        StructStringBuilder addField(const char* fieldName, T fieldValue) {
            _fields[fieldName] = fieldValue ? "true" : "false";

            return std::move(*this);
        }

        // Other arithmetic types
        template<typename T> requires (std::is_arithmetic_v<T> && !std::same_as<T, bool>)
        StructStringBuilder addField(const char* fieldName, T fieldValue) {
            _fields[fieldName] = std::to_string(fieldValue);

            return std::move(*this);
        }

        std::string build();
    };

}


#endif //VX_EMBER_STRUCTSTRINGBUILDER_H
