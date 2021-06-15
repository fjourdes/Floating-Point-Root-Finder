cmake_minimum_required(VERSION 3.1)

project(FloatingPointRootFinder)

# Visual studio solution directories.
set_property(GLOBAL PROPERTY USE_FOLDERS on)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(FPRF_TOPLEVEL_PROJECT ON)
else()
    set(FPRF_TOPLEVEL_PROJECT OFF)
endif()

include(GNUInstallDirs)

if(FPRF_TOPLEVEL_PROJECT)
    set(CMAKE_DEBUG_POSTFIX "_d")

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    if((CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT))
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Prefix prepended to install directories" FORCE)
        message(STATUS "Setting default CMAKE_INSTALL_PREFIX to: ${CMAKE_INSTALL_PREFIX}")
    endif()

    if(WIN32)
        if(NOT BUILD_SHARED_LIBS)
            message(STATUS "Using MSVC static runtime")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

            set(CMAKE_INSTALL_UCRT_LIBRARIES FALSE)
            set(CMAKE_INSTALL_OPENMP_LIBRARIES TRUE)
        else()
            set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
            set(CMAKE_INSTALL_OPENMP_LIBRARIES TRUE)
        endif()

        set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP FALSE)
        set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR})
        include(InstallRequiredSystemLibraries)
    endif()
endif()

find_package(Eigen3 REQUIRED)

add_library(FloatingPointRootFinder)

target_link_libraries(FloatingPointRootFinder PUBLIC Eigen3::Eigen)

file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB HEADER_FILES src/*.h)

set(FPRF_PUBLIC_HEADER_FILES
    include/CTCD.h
    include/Distance.h
    include/FPRF.h
    include/VelocityFilter.h
)


target_sources(FloatingPointRootFinder PRIVATE ${SOURCE_FILES})
target_sources(FloatingPointRootFinder PRIVATE ${HEADER_FILES})
target_sources(FloatingPointRootFinder PRIVATE ${FPRF_PUBLIC_HEADER_FILES})

target_include_directories(FloatingPointRootFinder
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(FloatingPointRootFinder PRIVATE "src" )

install(TARGETS FloatingPointRootFinder
        EXPORT FloatingPointRootFinderTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
)

foreach ( file ${FPRF_PUBLIC_HEADER_FILES} )
    get_filename_component( dir ${file} DIRECTORY )
    # use CMAKE_INSTALL_PREFIX instead of CMAKE_INSTALL_INCLUDEDIR since
    # each file has already a parent directory named "include"
    install( FILES ${file} DESTINATION ${CMAKE_INSTALL_PREFIX}/${dir} )
endforeach()

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/FloatingPointRootFinderConfig.cmake.in
    ${CMAKE_BINARY_DIR}/FloatingPointRootFinder/FloatingPointRootFinderConfig.cmake
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FloatingPointRootFinder"
)

install(FILES ${CMAKE_BINARY_DIR}/FloatingPointRootFinder/FloatingPointRootFinderConfig.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FloatingPointRootFinder")

install(EXPORT FloatingPointRootFinderTargets
        NAMESPACE "FPRF::"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FloatingPointRootFinder"
)

add_library(FPRF::FloatingPointRootFinder ALIAS FloatingPointRootFinder)

