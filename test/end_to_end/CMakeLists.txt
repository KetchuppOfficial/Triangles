add_executable(driver src/driver.cpp)
add_executable(generator src/generator.cpp)

target_link_libraries(driver
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_link_libraries(generator
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(driver
                           PRIVATE ${INCLUDE_DIR}
                           PRIVATE ${INCLUDE_DIR}/primitives
                           PRIVATE ${INCLUDE_DIR}/intersection
                           PRIVATE ${INCLUDE_DIR}/space_partitioning)

target_include_directories(generator
                           PRIVATE ${INCLUDE_DIR}
                           PRIVATE ${INCLUDE_DIR}/primitives)

install(TARGETS driver generator
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
