project(DtDataflowCore)
find_package(Corrade REQUIRED PluginManager)
find_package(imgui CONFIG REQUIRED)
find_package(Boost REQUIRED)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_library(DtDataflowCore
    src/base_node.cpp
    src/base_slot.cpp
    src/calculate_slot.cpp
    src/gui.cpp
    src/json.cpp
    src/number_slot.cpp
    src/string_slot.cpp
    src/any_slot.cpp
    src/value_less_slot.cpp
    src/window_node.cpp
    src/span_slot.cpp
    src/core_slot.cpp
    src/prototype_slot.cpp
    src/prototype_node.cpp
)
add_library(dt::DtDataflowCore ALIAS DtDataflowCore)
set_property(TARGET DtDataflowCore PROPERTY CXX_STANDARD 20)

generate_export_header(DtDataflowCore BASE_NAME DtDfCore)

target_include_directories(
    DtDataflowCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)
target_link_libraries(DtDataflowCore PRIVATE 
    Boost::headers
    imgui::imgui
    dt::imnodes
)
install(FILES
    ${PROJECT_BINARY_DIR}/dtdfcore_export.h
    DESTINATION include/dt/df/core
)
install(DIRECTORY include/ TYPE INCLUDE)
