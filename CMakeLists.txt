cmake_minimum_required(VERSION 3.15)
project(DtDataFlow
        VERSION 0.1.0
        DESCRIPTION "dataflow plugin base"
        HOMEPAGE_URL https://github.com/mathisloge/dt-dataflow
        LANGUAGES CXX
)
option(BUILD_SHARED_LIBS "build as a shared library" ON)
include(GenerateExportHeader)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_subdirectory(third-party)
add_subdirectory(core)
add_subdirectory(plugin)

install(TARGETS imnodes DtDataflowCore DtDataflowPlugin 
    EXPORT DtDataflowTargets
)

install(EXPORT DtDataflowTargets 
    FILE DtDataflowTargets.cmake
    DESTINATION lib/cmake/DtDataflow
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/DtDataflowConfig.cmake"
    INSTALL_DESTINATION lib/cmake/DtDataflow
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    DtDataflowConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT DtDataflowTargets
    FILE DtDataflowTargets.cmake
    NAMESPACE dt::
    DESTINATION lib/cmake/DtDataflow
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/DtDataflowConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/DtDataflowConfigVersion.cmake
    DESTINATION lib/cmake/DtDataflow
)
