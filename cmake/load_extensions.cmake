# Once done, this will define                                                                                                                                                                  
#                                                                               
#  MYSQL_INCLUDE_DIR - the MYSQL include directory                            
#  MYSQL_LIBRARY_DIR - the MYSQL library directory                            
#  SPDLG_LIBS - link these to use MYSQL                                        
#                                                                               
#  ......                                                                       
                                                                                
MACRO(LOAD_LIBMYSQL os arch)                                                   
    SET(EXTENSIONS_DIR ${PROJECT_SOURCE_DIR}/extensions/target/${${os}}_${${arch}}) 
    MESSAGE(STATUS "EXTENSIONS_DIR: ${EXTENSIONS_DIR}")                             
    FIND_FILE(MYSQL_INCLUDE_DIR include ${EXTENSIONS_DIR} NO_DEFAULT_PATH)          
    FIND_FILE(MYSQL_LIBRARY_DIR lib ${EXTENSIONS_DIR} NO_DEFAULT_PATH)           
                                                                                
    SET(MYSQL_LIBS                                                          
        mysql          
        pthread
        # PARENT_SCOPE no parent                                                 
    )                                                                           
    IF(MYSQL_INCLUDE_DIR)                                                      
        SET(MYSQL_LIBRARY_DIR "${MYSQL_LIBRARY_DIR}/mysql")               
        MESSAGE(STATUS "MYSQL_INCLUDE_DIR : ${MYSQL_INCLUDE_DIR}")            
        MESSAGE(STATUS "MYSQL_LIBRARY_DIR : ${MYSQL_LIBRARY_DIR}")            
        MESSAGE(STATUS "MYSQL_LIBS : ${MYSQL_LIBS}")                          
    ELSE()                                                                      
        MESSAGE(FATAL_ERROR "MYSQL_LIBS not found!")                           
    ENDIF()                                                                     
ENDMACRO()
