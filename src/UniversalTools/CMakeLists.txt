cmake_minimum_required(VERSION 3.5)

aux_source_directory(. CURRENT_DIR_SRCS)  
add_library(module_UniversalTools STATIC ${CURRENT_DIR_SRCS})

set_target_properties(module_UniversalTools PROPERTIES OUTPUT_NAME "UniversalTools")

set_target_properties(module_UniversalTools PROPERTIES DEBUG_POSTFIX d)