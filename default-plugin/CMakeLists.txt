project(DtDfPluginDefault)


set(SOURCES         
    src/protocol_ublox.cpp
    src/ublox_detail.cpp
    src/protocol_plugin.cpp
)
corrade_add_plugin(DtDfPluginDefault 
    "${DTDF_PLUGIN_INSTALL_DBG_DIR}"
    "${DTDF_PLUGIN_INSTALL_REL_DIR}"
    DtDfPluginDefault.conf 
    ${SOURCES}
)
set_property(TARGET DtDfPluginDefault PROPERTY CXX_STANDARD 20)

target_include_directories(
    DtDfPluginDefault PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_link_libraries(DtDfPluginDefault PRIVATE 
    dt::DtDfPlugin
)
