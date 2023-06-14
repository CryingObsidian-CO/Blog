cmake_minimum_required(VERSION 3.5)      
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)     

# PROJECT(Blog_test)

INCLUDE_DIRECTORIES(
    
    ${PROJECT_SOURCE_DIR}/src/Config/
)


enable_testing()

#test_JsonUtils
add_executable(test_JsonUtils ./test_JsonUtils.cpp)
add_test(NAME JsonUtils_test COMMAND test_JsonUtils)
set_tests_properties(JsonUtils_test PROPERTIES ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1")

