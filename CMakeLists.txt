cmake_minimum_required(VERSION 3.21)
project(Vx_Ember)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(third_party)

add_library(vxEmber STATIC source/core/Ember.h source/core/Ember.cpp source/core/nodes/Node.h source/core/NodeVisitor.h source/core/nodes/CameraNode.cpp source/core/nodes/CameraNode.h source/core/Pass.h source/passes/geometry_pass/GeometryPass.cpp source/passes/geometry_pass/GeometryPass.h source/core/nodes/SpatialNode.cpp source/core/nodes/SpatialNode.h source/core/nodes/Node.cpp source/core/Mesh.cpp source/core/Mesh.h source/core/Primitive.cpp source/core/Primitive.h source/passes/common/visitors/CameraLocatorVisitor.cpp source/passes/common/visitors/CameraLocatorVisitor.h source/core/visitors/NodeTraversalVisitor.cpp source/core/visitors/NodeTraversalVisitor.h source/core/NodeVisitor.cpp source/core/nodes/GeometryNode.cpp source/core/nodes/GeometryNode.h source/passes/common/visitors/GeometryRendererVisitor.cpp source/passes/common/visitors/GeometryRendererVisitor.h source/gl/Program.cpp source/gl/Program.h source/gl/Shader.cpp source/gl/Shader.h source/passes/matrix_update_pass/visitors/WorldMatrixUpdateVisitor.cpp source/passes/matrix_update_pass/visitors/WorldMatrixUpdateVisitor.h source/passes/matrix_update_pass/MatrixUpdatePass.cpp source/passes/matrix_update_pass/MatrixUpdatePass.h source/passes/presentation_pass/PresentationPass.cpp source/passes/presentation_pass/PresentationPass.h source/gltf/GLTFLoader.cpp source/gltf/GLTFLoader.h source/core/exceptions.h source/passes/imgui_pass/DebugImGuiPass.cpp source/passes/imgui_pass/DebugImGuiPass.h source/passes/imgui_pass/visitors/ImGuiTreeViewVisitor.cpp source/passes/imgui_pass/visitors/ImGuiTreeViewVisitor.h source/passes/rsm_pass/RSMPass.cpp source/passes/rsm_pass/RSMPass.h source/core/nodes/PointLightNode.cpp source/core/nodes/PointLightNode.h source/passes/common/visitors/LightLocatorVisitor.cpp source/passes/common/visitors/LightLocatorVisitor.h source/passes/common/RSMFramebuffer.cpp source/passes/common/RSMFramebuffer.h source/gl/BufferObject.cpp source/gl/BufferObject.h source/gl/VertexArrayObject.cpp source/gl/VertexArrayObject.h source/gl/Texture.cpp source/gl/Texture.h source/gl/Framebuffer.cpp source/gl/Framebuffer.h source/passes/gizmo_pass/GizmoPass.cpp source/passes/gizmo_pass/GizmoPass.h source/passes/gizmo_pass/visitors/GizmoRendererVisitor.cpp source/passes/gizmo_pass/visitors/GizmoRendererVisitor.h source/obj/OBJLoader.cpp source/obj/OBJLoader.h source/passes/common/RSMCache.cpp source/passes/common/RSMCache.h source/core/Material.cpp source/core/Material.h source/core/Image.cpp source/core/Image.h source/passes/common/BufferType.h source/passes/common/Frustum.cpp source/passes/common/Frustum.h source/passes/light_pass/LightPass.cpp source/passes/light_pass/LightPass.h)
target_link_libraries(vxEmber PRIVATE glm tinygltf imgui obj_loader spdlog::spdlog stb)
target_link_libraries(vxEmber INTERFACE tinygltf spdlog::spdlog)
target_include_directories(vxEmber PUBLIC ${CMAKE_SOURCE_DIR}/source)
target_compile_definitions(vxEmber PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

add_subdirectory(samples)