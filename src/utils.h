#ifndef UTILS_H
#define UTILS_H

// 回调函数类型定义，用于打印单个记录
typedef void (*PrintRecordFunc)(void* record, void* context);

// 分页显示函数
void displayWithPagination(
    void* records,           // 记录列表
    int totalRecords,        // 总记录数
    int recordsPerPage,      // 每页显示的记录数
    PrintRecordFunc print,   // 打印单个记录的回调函数
    void* context,           // 上下文数据（可选）
    const char* title        // 显示标题
);

#endif 