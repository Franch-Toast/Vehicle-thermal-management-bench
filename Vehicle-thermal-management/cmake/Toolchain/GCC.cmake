function(compilerVersion)
  execute_process(COMMAND "${CMAKE_C_COMPILER}" -dumpversion
     OUTPUT_VARIABLE CVERSION
     ERROR_VARIABLE CVERSION
    )
  SET(COMPILERVERSION ${CVERSION} PARENT_SCOPE)
  #cmake_print_variables(CVERSION)
  #cmake_print_variables(CMAKE_C_COMPILER)
  #MESSAGE( STATUS "CMD_OUTPUT:" ${CVERSION})
endfunction()

function(compilerSpecificCompileOptions PROJECTNAME ROOT)
  get_target_property(DISABLEOPTIM ${PROJECTNAME} DISABLEOPTIMIZATION)

  if (LITTLEENDIAN)
    target_compile_options(${PROJECTNAME} PUBLIC "-mlittle-endian")
  endif()

  if (CORTEXM OR CORTEXR)
    target_compile_options(${PROJECTNAME} PUBLIC "-mthumb")
  endif()

  target_link_options(${PROJECTNAME} PUBLIC "-mcpu=${ARM_CPU}")


  target_compile_options(${PROJECTNAME} PUBLIC "")
  target_link_options(${PROJECTNAME} PUBLIC "")

  target_link_options(${PROJECTNAME} PUBLIC "-specs=nosys.specs" )
  target_compile_options(${PROJECTNAME} PUBLIC "-specs=nosys.specs" )


  target_compile_options(${PROJECTNAME} PUBLIC 
    "-Wall"
    "-Werror=all"
    "-Wno-error=comment"
    "-g"
    "-O0"
    "-ffunction-sections"
    "-fdata-sections"
    "-Wno-error=unused-variable"
    "-Wno-error=unused-parameter"
    "-Wno-error=unused-function"
    "-Wno-error=unused-but-set-variable"
    "-Wno-error=unused-result"
    "-Wno-error=maybe-uninitialized"
    "-Wno-error=sign-compare"
    "-Wno-error=strict-aliasing"
    "-Wno-error=unknown-pragmas"
    "-Wno-error=format"
  )

 
  



endfunction()


function(compilerSpecificPlatformConfigLibForM PROJECTNAME ROOT)
 
endfunction()

function(compilerSpecificPlatformConfigLibForA PROJECTNAME ROOT)
  
endfunction()

function(compilerSpecificPlatformConfigLibForR PROJECTNAME ROOT)
 
endfunction()

function(compilerSpecificPlatformConfigAppForM PROJECTNAME ROOT)
  target_link_libraries(${PROJECTNAME} 
    "-Xlinker --gc-sections"
  )
endfunction()

function(compilerSpecificPlatformConfigAppForA PROJECTNAME ROOT)
  
endfunction()

function(compilerSpecificPlatformConfigAppForR PROJECTNAME ROOT)
 
endfunction()