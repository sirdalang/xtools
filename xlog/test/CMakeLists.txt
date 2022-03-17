project (xlog_test)

aux_source_directory(. src_xlog_test)

add_executable(${PROJECT_NAME} ${src_xlog_test})

target_link_libraries(${PROJECT_NAME} xlog)

include_directories(..)