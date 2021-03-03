find_package(imgui CONFIG REQUIRED)

if(TARGET imnodes)
    message(STATUS "imnodes target already existing")
else()
    message(STATUS "Adding imnodes")
    add_library(imnodes STATIC imnodes/imnodes.cpp)
    target_include_directories(imnodes PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imnodes>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(imnodes PRIVATE imgui::imgui)
    add_library(dt::imnodes ALIAS imnodes)
    install(FILES
        imnodes/imnodes.h
        DESTINATION include
    )
endif()
