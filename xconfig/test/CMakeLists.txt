project (xconfig_test)

aux_source_directory(. src_xconfig_test)

add_executable(${PROJECT_NAME} ${src_xconfig_test})

target_link_libraries(${PROJECT_NAME} xconfig)
target_link_libraries(${PROJECT_NAME} xlog)

include_directories(..)