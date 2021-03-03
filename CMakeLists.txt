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

install(TARGETS imgui-imnodes DtDataflowCore DtDataflowPlugin 
    EXPORT DtDataflowTargets
)

install(EXPORT DtDataflowTargets 
    FILE DtDataflowTargets.cmake
    DESTINATION lib/cmake/DtDataflow
)

include(CMakePackageConfigHelpers)
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
# todo: enable "docking-experimental" in vcpkg.json
