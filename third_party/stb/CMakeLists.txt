add_library(stb SHARED)
target_sources(stb PRIVATE stb_image.h stb_image.cpp)
target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})