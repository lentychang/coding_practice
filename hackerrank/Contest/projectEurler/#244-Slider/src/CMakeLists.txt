# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

file(GLOB files "*.cpp")
# foreach(file ${files})
#     string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${file})
#     set(FILENAME_WITHOUT_EXT ${CMAKE_MATCH_1})

#     get_filename_component(pure_name ${FILENAME_WITHOUT_EXT} NAME)

#     add_executable(${pure_name} ${file})
#     target_link_libraries(${pure_name} ${GTEST_LIBRARIES})
#     target_include_directories(${pure_name} PUBLIC ${GTEST_INCLUDE_DIRS})   
#     list(APPEND src_libs ${pure_name}_lib)
# endforeach(file)

add_executable(new_main new_main.cpp)
add_executable(main main.cpp)
# target_include_directories(new_main )


add_library(${CMAKE_PROJECT_NAME}Lib SHARED slider_map.cpp)
# target_include_directories()
target_link_libraries(new_main ${CMAKE_PROJECT_NAME}Lib)

# set(src_libs ${src_libs} PARENT_SCOPE)
# message(${src_libs})
# add_executable(${BINARY}_run ${SOURCES})
# add_library(${BINARY}_lib STATIC ${SOURCES})