aux_source_directory(./src SRC_LIST)

add_executable(basic_tests ${SRC_LIST})

target_link_libraries(basic_tests
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(basic_tests
                           PRIVATE ${INCLUDE_DIR}
                           PRIVATE ${INCLUDE_DIR}/primitives
                           PRIVATE ${INCLUDE_DIR}/intersection
                           PRIVATE ${INCLUDE_DIR}/space_partitioning)

gtest_discover_tests(basic_tests)
