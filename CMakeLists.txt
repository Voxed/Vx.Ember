cmake_minimum_required(VERSION 3.21)
project(Vx_Ember)

set(CMAKE_CXX_STANDARD 20)

add_library(vxEmber STATIC source/Ember.h source/Ember.cpp source/visitors/nodes/Node.h source/visitors/NodeVisitor.h source/visitors/nodes/CameraNode.cpp source/visitors/nodes/CameraNode.h source/passes/Pass.h source/passes/GeometryPass.cpp source/passes/GeometryPass.h)
target_include_directories(vxEmber PUBLIC ${CMAKE_SOURCE_DIR}/source)

add_subdirectory(samples)