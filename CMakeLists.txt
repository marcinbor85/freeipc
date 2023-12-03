cmake_minimum_required(VERSION 3.0)

project(freeipc LANGUAGES C VERSION 0.1.0)

enable_testing()

set (CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -pedantic -g -O0 --coverage -Wno-unused-parameter" )
set (CMAKE_C_FLAGS "-Werror -Wall -Wextra -pedantic -g -O0 --coverage -Wno-unused-parameter" )
set (CMAKE_EXE_LINKER_FLAGS "--coverage" )

add_library(
        freeipc
        STATIC
)

target_sources(
        freeipc
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src/ipc_get_time.c
        ${PROJECT_SOURCE_DIR}/src/ipc_hal.c
        ${PROJECT_SOURCE_DIR}/src/ipc_init.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_control.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_notify.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_register.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_request.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_response.c
        ${PROJECT_SOURCE_DIR}/src/ipc_node_service.c
        ${PROJECT_SOURCE_DIR}/src/ipc_service.c
)

target_include_directories(
        freeipc
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/example)
