cmake_minimum_required(VERSION 3.5)

aux_source_directory(. CURRENT_DIR_SRCS)  
aux_source_directory(./dto dto_CURRENT_DIR_SRCS)
add_library(module_WebServer ${CURRENT_DIR_SRCS} ${dto_CURRENT_DIR_SRCS})

set_target_properties(module_WebServer PROPERTIES OUTPUT_NAME "DataBase")

set_target_properties(module_WebServer PROPERTIES DEBUG_POSTFIX d)

target_link_libraries(module_WebServer oatpp)