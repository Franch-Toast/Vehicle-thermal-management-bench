SET(COMPILERVERSION "")

if (ARMAC6)
    include(${CMAKE_CURRENT_LIST_DIR}/AC6.cmake)
endif()

if (ARMAC5)
    include(${CMAKE_CURRENT_LIST_DIR}/AC5.cmake)
endif()

if (GCC)
    include(${CMAKE_CURRENT_LIST_DIR}/GCC.cmake)
endif()

if (ICCARM)
    include(${CMAKE_CURRENT_LIST_DIR}/ICCARM.cmake)
endif()

if ((MSVC) OR (HOST))
    function(compilerSpecificCompileOptions PROJECTNAME ROOT)
    endfunction()
endif()
