cmake_minimum_required(VERSION 3.0)
project(kms_demo)
set(CMAKE_CXX_STANDARD 11)
if(CMAKE_HOST_WIN32)
    include_directories("C:\\Program Files (x86)\\alibabacloud-sdk\\include")
    link_directories("C:\\Program Files (x86)\\alibabacloud-sdk\\lib")
endif()

add_executable(kms_demo kms.cc)
target_link_libraries(kms_demo alibabacloud-sdk-core alibabacloud-sdk-kms)

target_link_libraries(kms_demo)

set_target_properties(kms_demo
  PROPERTIES
  OUTPUT_NAME ${TARGET_OUTPUT_NAME_PREFIX}kms_demo
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
