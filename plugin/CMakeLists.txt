project(DtDfPlugin)

find_package(Corrade REQUIRED PluginManager)

add_library(DtDfPlugin INTERFACE)
add_library(dt::DtDfPlugin ALIAS DtDfPlugin)

target_include_directories(
    DtDfPlugin INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)
target_link_libraries(DtDfPlugin INTERFACE Corrade::PluginManager)
install(DIRECTORY include/ TYPE INCLUDE)
