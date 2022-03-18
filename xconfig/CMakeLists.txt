project (xconfig)

aux_source_directory(. src_xconfig)

add_library(${PROJECT_NAME} STATIC ${src_xconfig})

include_directories(${CMAKE_SOURCE_DIR}/xlog)

#get_property(dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
#message (">>>>>>> dirs=${dirs}")

add_subdirectory(test)