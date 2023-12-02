cmake_minimum_required(VERSION 3.0)

project(freeipc_example LANGUAGES C VERSION 0.1.0)

add_executable(linux_single_task
        ${PROJECT_SOURCE_DIR}/linux_single_task.c
        ${PROJECT_SOURCE_DIR}/../src/hal/linux_no_threads.c
)

target_link_libraries(linux_single_task freeipc)
