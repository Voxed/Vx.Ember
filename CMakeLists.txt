cmake_minimum_required(VERSION 3.21)
project(Vx_Ember)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)

add_library(vxEmber STATIC source/Ember.h source/Ember.cpp source/visitors/nodes/Node.h source/visitors/NodeVisitor.h source/visitors/nodes/CameraNode.cpp source/visitors/nodes/CameraNode.h source/passes/Pass.h source/passes/GeometryPass.cpp source/passes/GeometryPass.h source/visitors/nodes/SpatialNode.cpp source/visitors/nodes/SpatialNode.h source/visitors/nodes/Node.cpp source/Mesh.cpp source/Mesh.h source/Primitive.cpp source/Primitive.h source/visitors/CameraLocatorVisitor.cpp source/visitors/CameraLocatorVisitor.h source/visitors/NodeTraversalVisitor.cpp source/visitors/NodeTraversalVisitor.h source/visitors/NodeVisitor.cpp source/visitors/nodes/GeometryNode.cpp source/visitors/nodes/GeometryNode.h source/visitors/GeometryRendererVisitor.cpp source/visitors/GeometryRendererVisitor.h source/StructStringBuilder.cpp source/StructStringBuilder.h source/Program.cpp source/Program.h source/Shader.cpp source/Shader.h source/visitors/WorldMatrixUpdateVisitor.cpp source/visitors/WorldMatrixUpdateVisitor.h source/passes/MatrixUpdatePass.cpp source/passes/MatrixUpdatePass.h source/passes/PresentationPass.cpp source/passes/PresentationPass.h)
target_link_libraries(vxEmber PRIVATE glm)
target_include_directories(vxEmber PUBLIC ${CMAKE_SOURCE_DIR}/source)
add_subdirectory(third_party)
add_subdirectory(samples)