add_subdirectory(obj_loader)

add_library(imgui)
target_sources(imgui PRIVATE
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp)

target_include_directories(imgui PUBLIC imgui)

add_library(imgui_glfw)
target_sources(imgui_glfw PRIVATE
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp)

target_link_libraries(imgui_glfw imgui)

target_include_directories(imgui_glfw PUBLIC imgui/backends)

add_subdirectory(tinygltf)