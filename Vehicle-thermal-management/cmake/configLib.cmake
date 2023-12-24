# This is for building a library only
# It is similar to the config.cmake but ignoring anything related to the platform
# and boot code
if(EXPERIMENTAL)
list(APPEND CMAKE_MODULE_PATH ${EXPROOT})
include(experimental)
endif()


include(${CMAKE_CURRENT_LIST_DIR}/Toolchain/Tools.cmake)
option(OPTIMIZED "Compile for speed" OFF)
option(AUTOVECTORIZE "Prefer autovectorizable code to one using C intrinsics" OFF)

enable_language(CXX C ASM)


# Otherwise there is a .obj on windows and it creates problems
# with armlink. 
SET(CMAKE_C_OUTPUT_EXTENSION .o)
SET(CMAKE_CXX_OUTPUT_EXTENSION .o)
SET(CMAKE_ASM_OUTPUT_EXTENSION .o)

include(${CMAKE_CURRENT_LIST_DIR}/configCore.cmake)



