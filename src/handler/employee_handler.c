#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee_handler.h"
#include "../dal.h"
#include "../utils.h"

void handleAddEmployee(EmployeeList* list) {
    Employee emp;
    printf("\n=== 添加员工信息 ===\n");
    printf("请输入员工号：");
    scanf("%s", emp.id);
    
    if (findEmployee(list, emp.id) != NULL) {
        printf("该员工号已存在！\n");
        return;
    }
    
    printf("请输入姓名：");
    scanf("%s", emp.name);
    printf("请输入性别：");
    scanf("%s", emp.gender);
    printf("请输入出生年月(YYYY-MM)：");
    scanf("%s", emp.birthDate);
    
    addEmployee(list, emp);
    printf("员工信息添加成功！\n");
}

// 定义打印单个员工记录的回调函数
static void printEmployeeRecord(void* record, void* context) {
    EmployeeNode* emp = (EmployeeNode*)record;
    printf("员工号：%s\n", emp->data.id);
    printf("姓名：%s\n", emp->data.name);
    printf("性别：%s\n", emp->data.gender);
    printf("出生年月：%s\n", emp->data.birthDate);
}

// 获取下一个员工节点的函数
static void* getNextEmployee(void* node) {
    return ((EmployeeNode*)node)->next;
}

void handleDisplayAllEmployees(const EmployeeList* list) {
    if (list == NULL || list->head == NULL) {
        printf("暂无员工信息！\n");
        return;
    }

    displayWithPagination(
        list->head,           // 记录列表
        list->size,           // 总记录数
        5,                    // 每页显示5条记录
        printEmployeeRecord,  // 打印函数
        getNextEmployee,      // 获取下一个节点的函数
        NULL,                 // 不需要上下文
        "所有员工信息"        // 标题
    );
}

void handleFindEmployee(const EmployeeList* list) {
    char id[20];
    printf("\n=== 查找员工信息 ===\n");
    printf("请输入要查找的员工号：");
    scanf("%s", id);
    
    EmployeeNode* node = findEmployee(list, id);
    if (node != NULL) {
        printf("员工号：%s\n", node->data.id);
        printf("姓名：%s\n", node->data.name);
        printf("性别：%s\n", node->data.gender);
        printf("出生年月：%s\n", node->data.birthDate);
    } else {
        printf("未找到该员工！\n");
    }
}

void handleUpdateEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 修改员工信息 ===\n");
    printf("请输入要修改的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    Employee newData;
    strcpy(newData.id, id);
    printf("请输入新的姓名：");
    scanf("%s", newData.name);
    printf("请输入新的性别：");
    scanf("%s", newData.gender);
    printf("请输入新的出生年月(YYYY-MM)：");
    scanf("%s", newData.birthDate);
    
    updateEmployee(list, id, newData);
    printf("员工信息修改成功！\n");
}

void handleDeleteEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 删除员工信息 ===\n");
    printf("请输入要删除的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    deleteEmployee(list, id);
    printf("员工信息删除成功！\n");
}

void handleFindEmployeesByName(const EmployeeList* list) {
    char name[50];
    printf("\n=== 按姓名查找员工 ===\n");
    printf("请输入要查找的姓名（支持模糊查找）：");
    scanf("%s", name);
    
    EmployeeList* results = findEmployeesByName(list, name);
    if (results == NULL || results->size == 0) {
        printf("未找到匹配的员工！\n");
        if (results != NULL) {
            free(results);
        }
        return;
    }
    
    printf("\n找到 %d 个匹配的员工：\n", results->size);
    displayWithPagination(
        results->head,         // 记录列表
        results->size,         // 总记录数
        5,                     // 每页显示5条记录
        printEmployeeRecord,   // 打印函数
        getNextEmployee,       // 获取下一个节点的函数
        NULL,                  // 不需要上下文
        "查找结果"             // 标题
    );
    
    // 清理内存
    EmployeeNode* current = results->head;
    while (current != NULL) {
        EmployeeNode* next = current->next;
        free(current);
        current = next;
    }
    free(results);
} 