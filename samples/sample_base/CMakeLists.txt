add_library(sample_base STATIC source/SampleBase.h source/SampleBase.cpp)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(sample_base PUBLIC glfw OpenGL::OpenGL GLEW::GLEW)
target_include_directories(sample_base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)