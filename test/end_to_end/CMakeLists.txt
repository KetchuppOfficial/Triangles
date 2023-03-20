add_executable(driver src/driver.cpp)

target_link_libraries(driver
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                      PRIVATE m)

target_include_directories(driver
                           PRIVATE ${INCLUDE_DIR}
                           PRIVATE ${INCLUDE_DIR}/primitives
                           PRIVATE ${INCLUDE_DIR}/intersection
                           PRIVATE ${INCLUDE_DIR}/space_partitioning)

install(TARGETS driver
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
