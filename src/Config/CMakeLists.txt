cmake_minimum_required(VERSION 3.5)

aux_source_directory(. CURRENT_DIR_SRCS)  
add_library(module_Config STATIC ${CURRENT_DIR_SRCS})

set_target_properties(module_Config PROPERTIES OUTPUT_NAME "Config")

set_target_properties(module_Config PROPERTIES DEBUG_POSTFIX d)
