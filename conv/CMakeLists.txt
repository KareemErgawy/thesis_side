cmake_minimum_required(VERSION 2.8.9)
project(conv)

#set(ENV{OPENCLROOT} "/opt/AMD-APP-SDK")
set(ENV{OPENCLROOT} "C:/Program Files (x86)/Intel/OpenCL SDK/5.3/")

set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE EXTRA_FILES "src/*.cl")

############################################################################
# Find OpenCL include and libs
find_path( OPENCL_INCLUDE_DIRS 
    NAMES OpenCL/cl.h CL/cl.h
    HINTS $ENV{OPENCLROOT}/include/
)
mark_as_advanced(OPENCL_INCLUDE_DIRS)

find_library( OPENCL_LIBRARIES
    NAMES OpenCL
    HINTS $ENV{OPENCLROOT}/lib
    PATH_SUFFIXES ${PLATFORM}${BITNESS} ${BITNESS_SUFFIX}
)
mark_as_advanced( OPENCL_LIBRARIES )

if( OPENCL_INCLUDE_DIRS STREQUAL "" OR OPENCL_LIBRARIES STREQUAL "")
    message( FATAL_ERROR "Could not locate OpenCL include & libs" )
else ()
    message( STATUS "Found OpenCL")
endif( )

############################################################################

include_directories( ../shared src  ${OPENCL_INCLUDE_DIRS} ../../../../../include/SDKUtil $ENV{OPENCLROOT}/include/SDKUtil )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCE_FILES "src/main.cpp")

add_executable( conv ${SOURCE_FILES} ${INCLUDE_FILES} ${EXTRA_FILES})
target_link_libraries( conv ${OPENCL_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Copy extra files to binary directory
foreach( extra_file ${EXTRA_FILES} )
    add_custom_command(
        TARGET conv POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${extra_file}  ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${extra_file}  ./
        )
endforeach( extra_file )
