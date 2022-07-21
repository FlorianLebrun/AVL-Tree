set(target "ins.avl")
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/ins/avl/*.h")
add_library(${target} STATIC ${sources})
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
