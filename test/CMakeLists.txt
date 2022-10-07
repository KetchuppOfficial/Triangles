aux_source_directory(./basic_tests SRC_LIST)

add_executable(test_all ${SRC_LIST})

target_link_libraries(test_all
                      PRIVATE ${GTEST_LIBRARIES})

target_include_directories(test_all
                           PRIVATE ../include)

gtest_discover_tests(test_all)
