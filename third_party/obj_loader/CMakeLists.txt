add_library(obj_loader INTERFACE source/OBJ_Loader.h)
target_include_directories(obj_loader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/source)