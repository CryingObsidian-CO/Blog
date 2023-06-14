cmake_minimum_required(VERSION 3.5)      
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)                               

#--------------------------------------------                                   
# Project setting                                                               
#--------------------------------------------
include(cmake/messagecolor.cmake)                             
include(cmake/utils.cmake)    
include(cmake/load_extensions.cmake)   
define_colors()                                       
blog_project_extract_version()      

PROJECT(Blog VERSION ${BLOG_PROJECT_VERSION} LANGUAGES CXX) 

OPTION(BUILD_TESTS "Build with tests" ON)

MESSAGE(STATUS ${Blue} "--------------------------------")                                
MESSAGE(STATUS "Build Blog: ${BLOG_PROJECT_VERSION}")
MESSAGE(STATUS "Build with tests: ${BUILD_TESTS}")
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
IF (NOT CMAKE_TOOLCHAIN_FILE)
    MESSAGE(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
ENDIF()

#--------------------------------------------
# Set default build to debug
#--------------------------------------------
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
ENDIF()

MESSAGE(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

#--------------------------------------------
# Set compilation options
#--------------------------------------------
MESSAGE(STATUS ${Blue} "--------------------------------")                                      
                                                                                
IF(NOT TARGET_OS)                                                          
    SET(TARGET_OS Windows)                                                   
ENDIF()                                                                         
IF(NOT TARGET_ARCH)                                                        
    SET(TARGET_ARCH x86-64)                                                
ENDIF()   

MESSAGE(STATUS "Your target os : ${TARGET_OS}")                            
MESSAGE(STATUS "Your target arch : ${TARGET_ARCH}")
LOAD_LIBMYSQL(TARGET_OS TARGET_ARCH)

#--------------------------------------------
# Build extensions
#--------------------------------------------
MESSAGE(STATUS ${Blue} "--------------------------------")
# --------------------------------------------
add_subdirectory(extensions)

#--------------------------------------------
# Build application
#--------------------------------------------  
MESSAGE(STATUS ${Blue} "--------------------------------")
# defines targets and sources
add_subdirectory(src)

    

IF(BUILD_TESTS)
    MESSAGE(STATUS ${Blue} "--------------------------------")
    # add_subdirectory(tests)
ENDIF()