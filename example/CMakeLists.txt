cmake_minimum_required(VERSION 3.0)

project(freeipc_example LANGUAGES C VERSION 0.1.0)

add_executable(linux_single_task
        ${PROJECT_SOURCE_DIR}/linux_single_task.c
        ${PROJECT_SOURCE_DIR}/common.c
        ${PROJECT_SOURCE_DIR}/../src/hal/linux.c
)

target_link_libraries(linux_single_task freeipc)

add_executable(linux_multiple_tasks
        ${PROJECT_SOURCE_DIR}/linux_multiple_tasks.c
        ${PROJECT_SOURCE_DIR}/common.c
        ${PROJECT_SOURCE_DIR}/../src/hal/linux.c
)

target_link_libraries(linux_multiple_tasks freeipc)
