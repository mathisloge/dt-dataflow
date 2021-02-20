project(DtDfCore)
find_package(Corrade REQUIRED PluginManager)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_library(DtDfCore
    src/base_node.cpp
)
add_library(dt::DtDfCore ALIAS DtDfCore)
set_property(TARGET DtDfCore PROPERTY CXX_STANDARD 20)

generate_export_header(DtDfCore)

target_include_directories(
    DtDfCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)
target_link_libraries(DtDfCore PRIVATE 
    Boost::headers
    Boost::graph
    imgui::imgui
    imgui::imnodes
    sol2::sol2
)
install(DIRECTORY include/ TYPE INCLUDE)
