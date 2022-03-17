project (xlog)

aux_source_directory(. src_xlog)

add_library(${PROJECT_NAME} STATIC ${src_xlog})

add_subdirectory(test)