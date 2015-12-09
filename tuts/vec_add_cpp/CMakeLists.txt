cmake_minimum_required(VERSION 2.8.9)
project(vecadd_cpp)
set(ENV{AMDAPPSDKROOT} "/opt/AMD-APP-SDK")
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE EXTRA_FILES "src/*.cl")

############################################################################
# Find OpenCL include and libs
find_path( OPENCL_INCLUDE_DIRS 
    NAMES OpenCL/cl.h CL/cl.h
    HINTS $ENV{AMDAPPSDKROOT}/include/
)
mark_as_advanced(OPENCL_INCLUDE_DIRS)

find_library( OPENCL_LIBRARIES
    NAMES OpenCL
    HINTS $ENV{AMDAPPSDKROOT}/lib
    PATH_SUFFIXES ${PLATFORM}${BITNESS} ${BITNESS_SUFFIX}
)
mark_as_advanced( OPENCL_LIBRARIES )

if( OPENCL_INCLUDE_DIRS STREQUAL "" OR OPENCL_LIBRARIES STREQUAL "")
    message( FATAL_ERROR "Could not locate OpenCL include & libs" )
else ()
    message( STATUS "Found OpenCL")
endif( )

############################################################################

include_directories( src  ${OPENCL_INCLUDE_DIRS} ../../../../../include/SDKUtil $ENV{AMDAPPSDKROOT}/include/SDKUtil )

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCE_FILES "src/*.h")
file(GLOB SOURCE_FILES "src/*.cpp")

add_executable( vecadd_cpp ${SOURCE_FILES} ${INCLUDE_FILES} ${EXTRA_FILES})
target_link_libraries( vecadd_cpp ${OPENCL_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Copy extra files to binary directory
foreach( extra_file ${EXTRA_FILES} )
    add_custom_command(
        TARGET vecadd_cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${extra_file}  ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${extra_file}  ./
        )
endforeach( extra_file )
