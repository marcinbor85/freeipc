cmake_minimum_required(VERSION 3.10)

project(freeipc_test CXX)

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/../thirdparty/googletest thirparty/googletest)

function(create_test TARGET)
    add_executable(${TARGET})

    target_sources(${TARGET} PRIVATE
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${ARGN}
    )

    target_include_directories(${TARGET} PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/mocks
    )

    target_link_libraries(${TARGET}
        gmock_main
        gtest_main
    )
    
    add_test(${TARGET} ${TARGET})
endfunction()

add_subdirectory(tests)
