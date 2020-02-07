file(GLOB files "*.cpp")
# foreach(file ${files})
#     string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${file})
#     set(FILENAME_WITHOUT_EXT ${CMAKE_MATCH_1})

#     get_filename_component(pure_name ${FILENAME_WITHOUT_EXT} NAME)

#     add_executable(${pure_name} ${file})
#     target_include_directories(${pure_name} PUBLIC ${GTEST_INCLUDE_DIRS})   
#     target_link_libraries(${pure_name} PUBLIC ${CMAKE_PROJECT_NAME}_lib ${GTEST_LIBRARIES})

#     add_test(NAME ${pure_name} COMMAND ${pure_name})
# endforeach(file)

add_executable(unittest ${files})
enable_testing()
target_include_directories(unittest PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(unittest PRIVATE ${GTEST_LIBRARIES} ${CMAKE_PROJECT_NAME}Lib)
add_test(unittestSuite unittest)