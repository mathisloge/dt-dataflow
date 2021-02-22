find_package(imgui CONFIG REQUIRED)

if(not (TARGET imgui-imnodes))

add_library(imgui-imnodes STATIC imnodes/imnodes.cpp)
target_include_directories(imgui-imnodes PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imnodes>)
target_link_libraries(imgui-imnodes PRIVATE imgui::imgui)
add_library(imgui::imnodes ALIAS imgui-imnodes)
