project(DtDfPluginDefault)

find_package(imgui CONFIG REQUIRED)
find_package(Corrade REQUIRED PluginManager)

set(SOURCES         
    src/plugin.cpp
    src/slots/bool_slot.cpp
    src/slots/floating_slot.cpp
    src/slots/int_slot.cpp
    src/slots/trigger_slot.cpp
    src/slots/string_slot.cpp
)
message(STATUS "Plugin DBG Install dir: ${DTDF_PLUGIN_INSTALL_DBG_DIR}")
message(STATUS "Plugin REL Install dir: ${DTDF_PLUGIN_INSTALL_REL_DIR}")
corrade_add_plugin(DefaultPlugin 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    DtDfPluginDefault.conf 
    ${SOURCES}
)
set_property(TARGET DefaultPlugin PROPERTY CXX_STANDARD 20)

target_include_directories(
    DefaultPlugin PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(DefaultPlugin PRIVATE 
    imgui::imgui
    imgui::imnodes
    Corrade::PluginManager
    dt::DtDfCore
    dt::DtDfPlugin
)
