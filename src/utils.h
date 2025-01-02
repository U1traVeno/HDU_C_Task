#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
#include <windows.h>
#endif

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

// 字符串编码转换函数声明
#ifdef _WIN32
// 将UTF-8字符串转换为当前系统编码
char* convertUtf8ToCurrentEncoding(const char* utf8Str);
// 比较两个可能不同编码的字符串（用于搜索）
int compareStringWithEncoding(const char* str1, const char* str2);
// 释放转换后的字符串
void freeConvertedString(char* str);

void setConsoleEncoding();
#endif

#endif 