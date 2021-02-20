project(DtDfEditor)
find_package(Corrade REQUIRED PluginManager)
find_package(imgui CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS graph)

add_library(DtDfEditor 
    src/editor.cpp
    src/gui.cpp
    src/data_flow_graph.cpp
    src/graph_impl.cpp
    src/id_generator.cpp
    src/node_display_tree.cpp
    src/priv_types.cpp
)
add_library(dt::DtDfEditor ALIAS DtDfEditor)
set_property(TARGET DtDfEditor PROPERTY CXX_STANDARD 20)


set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

generate_export_header(DtDfEditor)

target_include_directories(
    DtDfEditor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)
target_link_libraries(DtDfEditor PRIVATE 
    Corrade::PluginManager
    Boost::headers
    Boost::graph
    imgui::imgui
    imgui::imnodes
    dt::DtDfCore
)
install(DIRECTORY include/ TYPE INCLUDE)

