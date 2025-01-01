cmake_minimum_required(VERSION 3.20)
project(HDU_C_Task C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 源文件列表
set(SOURCES
    # 主要源文件
    src/main.c
    src/cli.c
    src/cli.h
    src/dal.c
    src/dal.h
    src/model.h
    src/utils.h
    src/utils.c
    # handler模块
    src/handler/handler.c
    src/handler/handler.h
    src/handler/employee_handler.c
    src/handler/employee_handler.h
    src/handler/product_handler.c
    src/handler/product_handler.h
    src/handler/sale_handler.c
    src/handler/sale_handler.h
    src/handler/report_handler.c
    src/handler/report_handler.h
    src/test_data.c
    src/test_data.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 添加主要头文件搜索路径
target_include_directories(${PROJECT_NAME} PRIVATE src)
