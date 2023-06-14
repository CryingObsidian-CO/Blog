cmake_minimum_required(VERSION 3.5)

INCLUDE_DIRECTORIES(
    ./
    ./DataBase
    ./Logger
    ./Web
    ./Config
    ${PROJECT_SOURCE_DIR}/extensions/spdlog/include
    ${PROJECT_SOURCE_DIR}/extensions/target/**
    
    ${MYSQL_INCLUDE_DIR}
)

LINK_DIRECTORIES(
    ${MYSQL_LIBRARY_DIR}
)

# defines targets and sources
add_subdirectory(UniversalTools)
add_subdirectory(DataBase)
add_subdirectory(Logger)
add_subdirectory(Config)
add_subdirectory(Web)

# main.cpp                                                                      
set(SRC_LIST ./main.cpp)        
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})                         

# 配置可执行文件输出目录
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")
add_executable(Blog ${SRC_LIST})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

target_link_libraries(Blog module_UniversalTools)
target_link_libraries(Blog module_WebServer)
target_link_libraries(Blog module_DataBase)
target_link_libraries(Blog module_Logger)
target_link_libraries(Blog module_Config)