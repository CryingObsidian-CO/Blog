cmake_minimum_required(VERSION 3.5)

aux_source_directory(. CURRENT_DIR_SRCS)  
add_library(module_DataBase STATIC ${CURRENT_DIR_SRCS})

set_target_properties(module_DataBase PROPERTIES OUTPUT_NAME "DataBase")

set_target_properties(module_DataBase PROPERTIES DEBUG_POSTFIX d)


target_link_libraries(module_DataBase ${MYSQL_LIBS})