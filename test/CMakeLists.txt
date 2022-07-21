set(target AVLTree-test)
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
add_executable(${target} ${sources})
target_link_libraries(${target} PUBLIC "ins.avl")
