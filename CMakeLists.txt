cmake_minimum_required(VERSION 3.16)

project("AVL-Tree" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

add_subdirectory("./lib")
add_subdirectory("./test")
