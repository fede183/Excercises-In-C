

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()










string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")



message(STATUS "Conan toolchain: C++ Standard 17 with extensions ON")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Extra c, cxx, linkflags and defines


if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "/home/federico/.conan2/p/sfmle8955f48a0fa4/p/lib" "/home/federico/.conan2/p/freet43de8995d5bfe/p/lib" "/home/federico/.conan2/p/libpnae97cb4cc43f3/p/lib" "/home/federico/.conan2/p/zlib2229cab117a6f/p/lib" "/home/federico/.conan2/p/bzip247128e8043898/p/lib" "/home/federico/.conan2/p/brotl1464614398e2c/p/lib" "/home/federico/.conan2/p/flacc62a8e50a1be6/p/lib" "/home/federico/.conan2/p/opena3824387014a40/p/lib" "/home/federico/.conan2/p/libale1f75d2a3a991/p/lib" "/home/federico/.conan2/p/vorbie55c17566fd66/p/lib" "/home/federico/.conan2/p/ogg7497b524d42cf/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "/home/federico/.conan2/p/sfmle8955f48a0fa4/p/include" "/usr/include/uuid" "/home/federico/.conan2/p/freet43de8995d5bfe/p/include" "/home/federico/.conan2/p/freet43de8995d5bfe/p/include/freetype2" "/home/federico/.conan2/p/libpnae97cb4cc43f3/p/include" "/home/federico/.conan2/p/zlib2229cab117a6f/p/include" "/home/federico/.conan2/p/bzip247128e8043898/p/include" "/home/federico/.conan2/p/brotl1464614398e2c/p/include" "/home/federico/.conan2/p/brotl1464614398e2c/p/include/brotli" "/home/federico/.conan2/p/stbb3237e7146d86/p/include" "/home/federico/.conan2/p/flacc62a8e50a1be6/p/include" "/home/federico/.conan2/p/opena3824387014a40/p/include" "/home/federico/.conan2/p/opena3824387014a40/p/include/AL" "/home/federico/.conan2/p/libale1f75d2a3a991/p/include" "/home/federico/.conan2/p/vorbie55c17566fd66/p/include" "/home/federico/.conan2/p/ogg7497b524d42cf/p/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "/home/federico/Documents/Projects/Exercises-In-C/SFML Projects/template/build/build/Release/generators:$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "/home/federico/Documents/Projects/Exercises-In-C/SFML Projects/template/build/build/Release/generators:")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration
