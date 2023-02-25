aux_source_directory(./src SRC_LIST)

add_executable(algorithm_tests ${SRC_LIST})

target_link_libraries(algorithm_tests
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(algorithm_tests
                           PRIVATE ${INCLUDE_DIR}
                           PRIVATE ${INCLUDE_DIR}/primitives
                           PRIVATE ${INCLUDE_DIR}/intersection)

gtest_discover_tests(algorithm_tests)
