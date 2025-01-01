#ifndef UTILS_H
#define UTILS_H

// 回调函数类型定义，用于打印单个记录
typedef void (*PrintRecordFunc)(void* record, void* context);

// 回调函数类型定义，用于获取下一个节点
typedef void* (*GetNextFunc)(void* node);

// 分页显示函数
void displayWithPagination(
    void* records,           // 记录列表
    int totalRecords,        // 总记录数
    int recordsPerPage,      // 每页显示的记录数
    PrintRecordFunc print,   // 打印函数
    GetNextFunc getNext,     // 获取下一个节点的函数
    void* context,          // 上下文数据（可选）
    const char* title       // 显示标题
);

// 日期验证相关函数
int isLeapYear(int year);
int isValidDate(const char* dateStr);
int isValidYearMonth(const char* yearMonthStr);

#endif 