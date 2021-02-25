project(DtDataflowPlugin)

find_package(Corrade REQUIRED PluginManager)

add_library(DtDataflowPlugin INTERFACE)
add_library(dt::DtDataflowPlugin ALIAS DtDataflowPlugin)

target_include_directories(
    DtDataflowPlugin INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
)
target_link_libraries(DtDataflowPlugin INTERFACE Corrade::PluginManager)
install(DIRECTORY include/ TYPE INCLUDE)
