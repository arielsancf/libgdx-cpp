#Look for a directory containing STLport.
#
# The following values are defined
# GDXCPP_INCLUDE_DIR - where to find vector, etc.
# GDXCPP_LIBRARIES   - link against these to use STLport
# GDXCPP_FOUND       - True if the STLport is available.

# also defined, but not for general use are
IF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)
# in cache already
SET(GDXCPP_FIND_QUIETLY TRUE)
ENDIF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)

FIND_PATH(GDXCPP_INCLUDE_DIR
gdx-cpp/Gdx.hpp
PATHS
${GDX_SOURCE}/src
${GDX_ROOT}/include
/usr/local/include
/usr/include
/sw/include
/opt/local/include
/opt/csw/include
/opt/include
NO_CMAKE_FIND_ROOT_PATH
)

FIND_PATH(GDX_CPP_GDX_MACRO
gdx.cmake 
PATH_SUFFIXES
gdx/cmake
PATHS
${GDX_SOURCE}/cmake/
${GDX_ROOT}/share/gdx/cmake/
/usr/share/gdx/cmake/
/usr/local/share/gdx/cmake/
/opt/local/share/gdx/cmake/
NO_CMAKE_FIND_ROOT_PATH
)

include(${GDX_CPP_GDX_MACRO}/gdx.cmake)

macro(find_libraries)
    foreach(lib ${ARGV0})
        FIND_LIBRARY(GDXCPP_${lib}
            NAMES
            ${lib}
            libgdx-cpp-backend-android.a
            PATHS
            ${GDX_ROOT}
            /Users/mahmood1/Documents/test/android/gdx/lib
            PATH_SUFFIXES 
            lib
            lib/Release
            lib/Debug
            NO_CMAKE_FIND_ROOT_PATH
            )

        if (GDXCPP_${lib})
            LIST(APPEND GDXCPP_LIBRARIES "${GDXCPP_${lib}}")
        else()
            message(FATAL_ERROR "Could not find Libgdx library dependency:" ${lib})
            SET(GDXCPP_LIBRARIES GDXCPP_LIBRARIES-NOTFOUND)
            return(find_libraries)
        endif()
    endforeach()
endmacro()

if (APPLE)
    find_libraries(gdx-cpp)

    if (GdxCpp_USE_BOX2D)
        find_libraries("Box2D;gdx-cpp-box2d-layer")
    endif()
    
    find_libraries("gdx-cpp-backend-ios;gdx-cpp-agg-svg;")
elseif (UNIX)
    if (GdxCpp_USE_BOX2D)
        find_libraries("Box2D;gdx-cpp-box2d-layer")
    endif()
    
    if (ANDROID_NDK)
        set(GDXCPP_LIBRARIES "${GDXCPP_LIBRARIES};dl;log;GLESv1_CM;GLESv2;")
        find_libraries("gdx-cpp-backend-android;gdx-cpp-agg-svg;")
    else(ANDROID_NDK)
        if (GdxCpp_BUILD_GRAPHICS_GLES)
            find_libraries("GLESv1_CM;GLESv2")
        else()
            find_libraries("GL")
        endif()

        find_libraries("vorbis;vorbisfile;openal;ogg;SDL;GLU;gdx-cpp-backend-linux;gdx-cpp-agg-svg;pthread;rt;")
    endif()

    find_libraries(gdx-cpp)
endif()

if(GDXCPP_INCLUDE_DIR)
    if(GDXCPP_LIBRARIES)
        set(GDXCPP_FOUND TRUE)
    endif(GDXCPP_LIBRARIES)
endif(GDXCPP_INCLUDE_DIR)

if(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        foreach(LIB ${GDXCP_LIBRARIES})
           message("Found GDX Library: " ${LIB})
        endforeach()
    endif()
else(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        message(STATUS "Warning: Unable to find GdxCPP!")
    endif()
endif(GDXCPP_FOUND)

MARK_AS_ADVANCED(GDXCPP_LIBRARY)
