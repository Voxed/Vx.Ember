cmake_minimum_required(VERSION 3.21)
project(Vx_Ember)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)

add_subdirectory(third_party)

add_library(vxEmber STATIC source/Ember.h source/Ember.cpp source/visitors/nodes/Node.h source/visitors/NodeVisitor.h source/visitors/nodes/CameraNode.cpp source/visitors/nodes/CameraNode.h source/passes/Pass.h source/passes/GeometryPass.cpp source/passes/GeometryPass.h source/visitors/nodes/SpatialNode.cpp source/visitors/nodes/SpatialNode.h source/visitors/nodes/Node.cpp source/Mesh.cpp source/Mesh.h source/Primitive.cpp source/Primitive.h source/visitors/CameraLocatorVisitor.cpp source/visitors/CameraLocatorVisitor.h source/visitors/NodeTraversalVisitor.cpp source/visitors/NodeTraversalVisitor.h source/visitors/NodeVisitor.cpp source/visitors/nodes/GeometryNode.cpp source/visitors/nodes/GeometryNode.h source/visitors/GeometryRendererVisitor.cpp source/visitors/GeometryRendererVisitor.h source/StructStringBuilder.cpp source/StructStringBuilder.h source/gl/Program.cpp source/gl/Program.h source/gl/Shader.cpp source/gl/Shader.h source/visitors/WorldMatrixUpdateVisitor.cpp source/visitors/WorldMatrixUpdateVisitor.h source/passes/MatrixUpdatePass.cpp source/passes/MatrixUpdatePass.h source/passes/PresentationPass.cpp source/passes/PresentationPass.h source/gltf/GLTFLoader.cpp source/gltf/GLTFLoader.h source/exceptions.h source/passes/DebugImGuiPass.cpp source/passes/DebugImGuiPass.h source/visitors/ImGuiTreeViewVisitor.cpp source/visitors/ImGuiTreeViewVisitor.h source/passes/RSMPass.cpp source/passes/RSMPass.h source/GeometryFramebuffer.cpp source/GeometryFramebuffer.h source/visitors/nodes/PointLightNode.cpp source/visitors/nodes/PointLightNode.h source/visitors/LightLocatorVisitor.cpp source/visitors/LightLocatorVisitor.h source/RSMFramebuffer.cpp source/RSMFramebuffer.h source/gl/BufferObject.cpp source/gl/BufferObject.h source/gl/VertexArrayObject.cpp source/gl/VertexArrayObject.h source/gl/Texture.cpp source/gl/Texture.h source/gl/Framebuffer.cpp source/gl/Framebuffer.h source/passes/GizmoPass.cpp source/passes/GizmoPass.h source/visitors/GizmoRendererVisitor.cpp source/visitors/GizmoRendererVisitor.h source/obj/OBJLoader.cpp source/obj/OBJLoader.h)
target_link_libraries(vxEmber PRIVATE glm tinygltf imgui obj_loader)
target_link_libraries(vxEmber INTERFACE tinygltf)
target_include_directories(vxEmber PUBLIC ${CMAKE_SOURCE_DIR}/source)

add_subdirectory(samples)