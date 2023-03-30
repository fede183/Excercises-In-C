########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libalsa_COMPONENT_NAMES "")
set(libalsa_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(libalsa_PACKAGE_FOLDER_RELEASE "/home/federico/.conan2/p/libale1f75d2a3a991/p")
set(libalsa_BUILD_MODULES_PATHS_RELEASE )


set(libalsa_INCLUDE_DIRS_RELEASE )
set(libalsa_RES_DIRS_RELEASE "${libalsa_PACKAGE_FOLDER_RELEASE}/res")
set(libalsa_DEFINITIONS_RELEASE )
set(libalsa_SHARED_LINK_FLAGS_RELEASE )
set(libalsa_EXE_LINK_FLAGS_RELEASE )
set(libalsa_OBJECTS_RELEASE )
set(libalsa_COMPILE_DEFINITIONS_RELEASE )
set(libalsa_COMPILE_OPTIONS_C_RELEASE )
set(libalsa_COMPILE_OPTIONS_CXX_RELEASE )
set(libalsa_LIB_DIRS_RELEASE "${libalsa_PACKAGE_FOLDER_RELEASE}/lib")
set(libalsa_BIN_DIRS_RELEASE )
set(libalsa_LIBRARY_TYPE_RELEASE STATIC)
set(libalsa_IS_HOST_WINDOWS_RELEASE 0)
set(libalsa_LIBS_RELEASE asound)
set(libalsa_SYSTEM_LIBS_RELEASE dl m rt pthread)
set(libalsa_FRAMEWORK_DIRS_RELEASE )
set(libalsa_FRAMEWORKS_RELEASE )
set(libalsa_BUILD_DIRS_RELEASE )
set(libalsa_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libalsa_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libalsa_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libalsa_COMPILE_OPTIONS_C_RELEASE}>")
set(libalsa_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libalsa_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libalsa_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libalsa_EXE_LINK_FLAGS_RELEASE}>")


set(libalsa_COMPONENTS_RELEASE )