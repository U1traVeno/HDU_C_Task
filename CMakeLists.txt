cmake_minimum_required(VERSION 3.20)
project(HDU_C_Task C)

# 设置 C23 标准
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 显式列出所有源文件
set(SOURCES
    src/main.c
    src/cli.c
    src/dal.c
    src/handler.c
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE src)
