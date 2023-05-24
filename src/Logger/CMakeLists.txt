cmake_minimum_required(VERSION 3.5)

aux_source_directory(. CURRENT_DIR_SRCS)  
add_library(module_Logger STATIC ${CURRENT_DIR_SRCS})

set_target_properties(module_Logger PROPERTIES OUTPUT_NAME "Logger")

set_target_properties(module_Logger PROPERTIES DEBUG_POSTFIX d)

# target_link_libraries(module_Logger spdlog)

# add_library(module_Logger "")
# target_sources(module_DataBase
#   PUBLIC
#       ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
#   )

# target_include_directories(module_DataBase
# PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${MYSQL_INCLUDE_DIR}
# )